#include "minishell.h"

void	print_2dim_string(char **s, size_t size)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (i < size)
		{
			fprintf(stderr, "[%zu] %s$\n", i, s[i]);
			i++;
		}
	}
	fprintf(stderr, "$----------------end--------------$\n\n");
}

void	print_err_msg(char *msg, char *str, char *msg2)
{
	char	*temp;
	char	*temp2;

	if (str != NULL)
		temp = ft_strjoin(msg, str);
	else
		temp = ft_strdup(msg);
	temp2 = ft_strjoin(temp, msg2);
	write(STDERR_FILENO, temp2, ft_strlen(temp2));
	ft_memdel(&temp);
	ft_memdel(&temp2);
}

char	**check_valid_readline(t_minishell *msh, char *line)
{
	char	**args;
	char	**new_args;
	size_t	size;
	size_t	i;
/*
	printf("strnstr(line, <<)=%s\n", ft_strnstr(line, "<<", 2));
	printf("strstr(line, <<)=%s\n", ft_strstr(line, "<<"));
	printf("%c, %s\n", line[ft_strlen(line) - 1], line + 2);
	printf("strcmp =%d\n", ft_strcmp(line + (ft_strlen(line) - 2), "<<"));
	printf("strncmp =%d\n", ft_strncmp(line, "<<", 2));
	printf("string count=%zu\n", get_string_count(line, "<<"));
*/
	//printf("strnstr(line, NULL)=%s\n", ft_strnstr(line, NULL, 1));
	//args = split_readline(msh->cmd.line);
	//args = split_readline_by_argc(msh, msh->cmd[0].line);
	args = NULL;
	args = split_readline_by_argc(msh, args, line);
	//fprintf(stderr, "check valid readline af split readline argc=%zu\n", check_readline_argc(msh->cmd[0].line));
	if (args == NULL)
	{
		//fprintf(stderr, "args is nulln");
		return ((char **) NULL);
	}
/*
	args = check_valid_pipeline(msh, args, ft_strlen_2dim((const char **)args));
	if (args == NULL)
		return ((char **) NULL);
*/
	msh->cmd[0].pipe_count = check_pipe_count(args, -1);
	args = check_redirection_variable(msh, &msh->cmd[0], args);
	if (args == NULL)
		return ((char **) NULL);
	args = check_valid_redirection(msh, &msh->cmd[0], args);
	check_variables(msh, &args);
	return (args);
}

int	check_readline(t_minishell *msh, char **line)
{
	size_t	i;
	int	err;
	//int	pipe_count;

	//if (msh->cmd.args != NULL)
	//	ft_memdel_2dim(&(msh->cmd.args));
	err = check_quotes(msh, line);
	if (err == 1)
		return (1);
	else if (err == 2)
	{
		msh->exit_status = 2;
		//fprintf(stderr, "af ch qu exit status=%d\n", msh->exit_status);
		return (1);
	}
	err = check_pipeline(msh, line);
	if (err == 1)
		return (1);
	else if (err == 2)
	{
		msh->exit_status = 2;
		//fprintf(stderr, "af ch pi exit status=%d\n", msh->exit_status);
		return (1);
	}
/*
	fprintf(stderr, "single=%d, double=%d\n", msh->cmd.flags.q_single, msh->cmd.flags.q_double);
	fprintf(stderr, "-----------------\nnew line=%s$\n--------------\n", msh->cmd.line);
	fprintf(stderr, "-----------------\nline=%s$\n--------------\n", line);
*/

	msh->cmd[0].line = ft_strdup(*line);
	//msh->cmd[0].line = (*line);
	msh->cmd[0].args = check_valid_readline(msh, *line);
	if (msh->cmd[0].args == NULL)
	{
		free_cmd(&msh->cmd[0], 0);
		return (1);
	}
	//fprintf(stderr, "args[0]=%s\n", msh->cmd[0].args[0]);
	//fprintf(stderr, "-----------------readline--------------\n");
	//print_2dim_string(msh->cmd[0].args, ft_strlen_2dim((const char **)msh->cmd[0].args));
	//msh->args = split_pipe_charater(msh->args);
	//if (ft_strchr(cmd, '\n') != NULL)
		//printf("%c\n", cmd[ft_strlen(cmd)]);
	//	cmd[ft_strlen(cmd) - 1] = '\0';
	//printf("sizeof(cmd)=%d, strlen(cmd)=%d\n", sizeof(cmd), strlen(cmd));
		//ft_export3(msh->cmd[0].args, msh->envp);
	//else if (ft_strncmp(msh->cmd[0].args[0], "env", 3) == 0)
	//	ft_env(msh->envp);
	if (msh->cmd[0].pipe_count)
		msh->exit_status = run_pipe_commands(msh, &msh->cmd[0], msh->cmd[0].pipe_count);
	else if (ft_strcmp(msh->cmd[0].args[0], "cd") == 0)
		ft_cd(msh, msh->cmd[0].args, 0);
	else if (ft_strcmp(msh->cmd[0].args[0], "unset") == 0)
		ft_unset(msh, msh->cmd[0].args);
	else if (ft_strcmp(msh->cmd[0].args[0], "exit") == 0)
		msh->exit_status = ft_exit(msh, msh->cmd[0].args);
	else if (ft_strcmp(msh->cmd[0].args[0], "export") == 0)
		ft_export(msh, msh->cmd[0].args);
	else
		msh->exit_status = run_one_command(msh, &msh->cmd[0]);
	free_cmd(&msh->cmd[0], 0);
	//fprintf(stderr, "finishing check_readline\n");
	return (0);
}

int	ft_readline(t_minishell *msh)
{
	char	*line;

	while (1)
	{
		listen_signals();
		line = readline("minishell$ ");
		if (line)
		{
			check_readline(msh, &line);
			if (msh->ret != NULL)
			{
				ft_memdel(&line);
				return (1);
			}
		}
		else
		{
			ft_memdel(&line);
			break ;
		}
		if (check_readline_argc(line) > 0)
			add_history(line);
		ft_memdel(&line);
	}
	ft_memdel(&line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	//t_minishell	msh;

	init_msh(&msh, envp);
	ft_readline(&msh);
	if (msh.ret != NULL)
	{
		printf("%s\n", msh.ret);
		ft_memdel(&msh.ret);
		free_msh(&msh, 0);
		return (1);
	}
	free_msh(&msh, 0);
	return (0);
}
