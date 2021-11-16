#include "minishell.h"

void	ft_execve(t_minishell *msh, char **args)
{
	char	**paths;
	char	*new_path;
	char	*current_path;
	size_t	i;
	size_t	size;

	i = 0;
	while (ft_strncmp(msh->envp[i], "PATH", 4) != 0)
		i++;
	paths = ft_split(msh->envp[i] + 5, ':');
	size = ft_strlen_2dim((const char **)paths);
	i = 0;
	while (i < size)
	{
		current_path = ft_strjoin(paths[i], "/");
		new_path = ft_strjoin(current_path, args[0]);
		execve(new_path, args, msh->envp);
		free(current_path);
		free(new_path);
		i++;
	}
	ft_memdel_2dim(&paths);
	msh->ret = ft_strjoin(args[0], ": command not found");
}


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

char	*ft_itos(int c)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * 2);
	if (!dst)
		return (NULL);
	dst[0] = c;
	dst[1] = '\0';
	return (dst);
}

size_t	check_readline_argc(char *line)
{
	size_t	argc;
	size_t	i;
	size_t	size;

	size = ft_strlen(line);
	i = 0;
	argc = 0;
	while (i < size)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == Q_SINGLE)
		{
			argc++;
			//i += check_single_quote((line + i + 1), &argc);
			i += check_single_quote((line + i + 1), &argc);
			//fprintf(stderr, "line[%zu]=%c\n", i - 1, line[i - 1]);
			//fprintf(stderr, "line[%zu]=%c\n", i, line[i]);
		}
		else if (line[i] == Q_DOUBLE)
		{
			argc++;
			i += check_double_quote((line + i + 1), &argc);
		}
		else if (line[i] >= 33 && line[i] <= 126)
		{
			argc++;
			while (line[i + 1] != ' ' && line[i + 1] != '\0')
				i++;
		}
		//msh->cmd.args = ft_strjoin_2dim_memdel(msh->cmd.args, malloc_args(msh, ));
		i++;
	}
	return (argc);
}

char	*search_one_variable(t_minishell *msh, char *variable)
{
	size_t	i;

	i = 0;
	while (ft_strcmp(msh->envp[i], variable) != 0)
		i++;
	return (msh->envp[i]);
}

char	*parse_variables(t_minishell *msh, char *line)
{
	char	*temp;
	size_t	size;
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		i++;
	}
	return (NULL);
}


static size_t check_semicolon_character(char *line)
{
	size_t	i;
	size_t	last;

	i = 0;
	//printf("line=%s$, last ch=%c$\n", line, line[ft_strlen(line) - 1]);
	//last = 0;
	while (i < ft_strlen(line))// && line[i] != '\0')
	{
		while (line[i] == ' ')
			i++;
		if ((line[i] >= 33 && line[i] <= 126))
		{
			while (line[i + 1] != ' ' && line[i + 1] != '\0')
				i++;
			last = i;
		}
		i++;
	}
	//printf("last=%d$, line[last]=%c\n", last, line[last]);
	if (line[last] == ';')
		return (1);
	else
		return (0);
}
/*
char	**check_valid_semicolon(t_minishell *msh, char **args, char *line)
{
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen_2dim((const char **)args);
	if (check_syntax_error(msh, args, size) == 1)
		return ((char **) NULL);
	i = 0;
	while (i < size)
	{
		//if (!ft_strcmp(args[i], ";")
		if (!ft_strcmp(args[i], ";") && args[i + 1] != NULL)
			msh->cmd_count++;
			//count++;
		i++;
	}
	if (msh->cmd_count > 1)
	{
		if (msh->cmd != NULL)
		{
			free_cmd(&msh->cmd[0]);
			free(msh->cmd);
		}
		msh->cmd = (t_cmd)malloc(sizeof(t_cmd) * (msh->cmd_count));
		if (!msh->cmd)
			return ((char **) NULL);
		i = 0;
		while (i < msh->cmd_count)
			init_cmd(&msh->cmd[i++]);
	}
	if (check_semicolon((args) + i) != 0)
		i = check_semicolon((args) + i);
}
*/
char	**check_valid_readline(t_minishell *msh, char *line)
{
	char	**args;
	char	**new_args;
	size_t	size;
	size_t	i;
	//printf("var=%s\n", search_one_variable(msh, "VAR1"));

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
	args = split_readline_by_argc(msh, line);
	//fprintf(stderr, "check valid readline af split readline argc=%zu\n", check_readline_argc(msh->cmd[0].line));
	if (args == NULL)
	{
		fprintf(stderr, "args is nulln");
		return ((char **) NULL);
	}
/*
	args = check_valid_pipeline(msh, args, ft_strlen_2dim((const char **)args));
	if (args == NULL)
		return ((char **) NULL);
*/
	msh->cmd[0].pipe_count = check_pipe_count(args, -1);
	args = check_valid_redirection(msh, &msh->cmd[0], args);
	return (args);
}


int	check_readline(t_minishell *msh, char **line)
{
	size_t	i;
	//int	pipe_count;

	//if (msh->cmd.args != NULL)
	//	ft_memdel_2dim(&(msh->cmd.args));
	if (check_quotes(msh, line) == 1)
		return (1);
	if (check_pipeline(msh, line) == 1)
		return (1);
/*
	fprintf(stderr, "single=%d, double=%d\n", msh->cmd.flags.q_single, msh->cmd.flags.q_double);
	fprintf(stderr, "-----------------\nnew line=%s$\n--------------\n", msh->cmd.line);
	fprintf(stderr, "-----------------\nline=%s$\n--------------\n", line);
*/

	msh->cmd[0].line = ft_strdup(*line);
	msh->cmd[0].args = check_valid_readline(msh, *line);
	fprintf(stderr, "-----------------readline--------------\n");
	print_2dim_string(msh->cmd[0].args, ft_strlen_2dim((const char **)msh->cmd[0].args));
	if (msh->cmd[0].args == NULL)
	{
		free_cmd(&msh->cmd[0]);
		return (1);
	}
	//msh->args = split_pipe_charater(msh->args);
	//if (ft_strchr(cmd, '\n') != NULL)
		//printf("%c\n", cmd[ft_strlen(cmd)]);
	//	cmd[ft_strlen(cmd) - 1] = '\0';
	//printf("sizeof(cmd)=%d, strlen(cmd)=%d\n", sizeof(cmd), strlen(cmd));
	if (msh->cmd[0].pipe_count)
		run_pipe_commands(msh, &msh->cmd[0], msh->cmd[0].pipe_count);
	else
		run_one_command(msh, &msh->cmd[0]);
	free_cmd(&msh->cmd[0]);
	return (0);
/*
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
	{
	}
	else
	{
		printf("command not found: %s\n", cmd);
	}
*/
}

int	ft_readline(t_minishell *msh)
{
	char	*line;

	while (1)
	{
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
		add_history(line);
		ft_memdel(&line);
	}
	ft_memdel(&line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	msh;

	init_msh(&msh, envp);
	ft_readline(&msh);
	if (msh.ret != NULL)
	{
		printf("%s\n", msh.ret);
		ft_memdel(&msh.ret);
		free_msh(&msh);
		return (1);
	}
	free_msh(&msh);
	return (0);
}
