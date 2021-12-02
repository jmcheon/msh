#include "minishell.h"

int	open_infile(char *token, char *infile_path, int *infile)
{
	char	*temp_path;

	temp_path = NULL;
	if (!ft_strcmp(token, "<<"))
	{
		temp_path = ft_strjoin(HEREDOC_PATH, infile_path);
		*infile = open(temp_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
	}
	else
		*infile = open(infile_path, O_RDONLY);
	if (*infile == -1)
	{
		ft_memdel(&temp_path);
		return (1);
	}
	ft_memdel(&temp_path);
	return (0);
}

static int	get_next_heredoc_old(t_minishell *msh, t_cmd *cmd, char **args, int infile)
{
	char	*temp;
	char	*line;
	int		argc;
	int		ret;

	temp = NULL;
		line = NULL;
	argc = 0;
	ret = 1;
	if (!ft_strcmp(args[0], "<<"))
	{
		ft_memdel(&cmd->temp_path);
		
		temp = omit_quotes(args[1]);
		cmd->temp_path = ft_strjoin(HEREDOC_PATH, temp);
		write(STDIN_FILENO, "> ", 2);
		while (ret)
		{
			ret = get_next_line(&line);
			if (!ft_strcmp(line, temp))
			{
				fprintf(stderr, "end of file with=%s\n", temp);
				ft_memdel(&line);
				break ;
			}
			argc = check_readline_argc(line);
			if (argc == 0 && ret < 1)
			{
				if (execute_syntax_error(msh, temp, -4))
				{
					fprintf(stderr, "argc, ret = (%d, %d) finished by ctrl d, %s\n", argc, ret, temp);
					close(infile);
					ft_memdel(&line);
					ft_memdel(&temp);
					exit (0);
					//return (0);
				}
			}
			else
			{
				write(STDIN_FILENO, "> ", 2);
				write(infile, line, ft_strlen(line));
				write(infile, "\n", 1);
				ft_memdel(&line);
			}
		}
		close(infile);
		ft_memdel(&line);
		ft_memdel(&temp);
	}
			ft_memdel(&line);
	return (0);
}

static int	get_next_heredoc(t_minishell *msh, t_cmd *cmd, char **args, int infile)
{
	char	*temp;
	char	*line;
	int		argc;
	int		ret;

	temp = NULL;
	line = NULL;
	argc = 0;
	ret = 1;
	if (!ft_strcmp(args[0], "<<"))
	{
		ft_memdel(&cmd->temp_path);
		temp = omit_quotes(args[1]);
		msh->heredoc_limiter = args[1];
		cmd->temp_path = ft_strjoin(HEREDOC_PATH, temp);
		//write(STDIN_FILENO, "> ", 2);
		msh->running_heredoc = 1;
		listen_signals_heredoc();
		while (1)
		{
			line = readline(">>");
			if (line)
			{
				if (!ft_strcmp(line, temp))
				{
					//fprintf(stderr, "end of file with=%s\n", temp);
					ft_memdel(&line);
					break ;
				}
				check_variables(msh, &args);
				argc = check_readline_argc(line);
				//if (argc == 0 && ret < 1)
				//fprintf(stderr, "line=%s$, argc=%d\n", line, argc);
		//		else
				{
					write(infile, line, ft_strlen(line));
					write(infile, "\n", 1);
					ft_memdel(&line);
				}
	/*
				check_readline(msh, &line);
				if (msh->ret != NULL)
				{
					ft_memdel(&line);
					return (1);
				}
*/
			}
			else
			{
				ft_memdel(&line);
				break ;
			}
			ft_memdel(&line);
		}
		msh->running_heredoc = 0;
		//fprintf(stderr, "end of heredoc\n");
		dup2(msh->stdfd[0], STDIN_FILENO);
		dup2(msh->stdfd[1], STDOUT_FILENO);
		//dup2(msh->stdfd[0], STDIN_FILENO);	
		close(msh->stdfd[0]);
		close(msh->stdfd[1]);
		msh->stdfd[0] = dup(STDIN_FILENO);
		msh->stdfd[1] = dup(STDOUT_FILENO);
/*
		argc = check_readline_argc(line);
		fprintf(stderr, "heredoc fini=%s$, argc=%d\n", line, argc);
		if (argc == 0 && line == NULL)
		{
			printf("msh: syntax error: unexpected end of file (wanted '%s')\n", temp);
			//if (execute_syntax_error(msh, temp, -4))
			{
				fprintf(stderr, "argc, ret = (%d, %d) finished by ctrl d, %s\n", argc, ret, temp);
				close(infile);
				ft_memdel(&line);
				ft_memdel(&temp);
				//free_msh(msh);
				//exit (0);
				return (0);
			}
		}
*/
		ft_memdel(&line);
		ft_memdel(&temp);
	}
	return (0);
}

int	execute_heredoc(t_minishell *msh, t_cmd *cmd, char **args)
{
	char	*temp_path;
	char	*temp;
	char	*line;
	int		infile;

	temp = NULL;
	temp_path = omit_quotes(args[1]);
	if (open_infile(args[0], temp_path, &infile) == 1)
	{
		if (msh->ret == NULL)
		{
			temp = ft_strjoin(temp_path, ": ");
			msh->ret = ft_strjoin(temp, strerror(errno));
			ft_memdel(&temp);
			msh->exit_status = 1;
		}
		return (1);
	}
	ft_memdel(&temp_path);
	if (get_next_heredoc(msh, cmd, args, infile) == 1)
		return (1);
	return (0);
}

int	redirect_input(t_minishell *msh, char **args)
{
	char	*temp;
	char	*line;
	int		infile;

	temp = NULL;
	if (open_infile(args[0], args[1], &infile) == 1)
	{
		if (msh->ret == NULL)
		{
			temp = ft_strjoin(args[1], ": ");
			msh->ret = ft_strjoin(temp, strerror(errno));
			ft_memdel(&temp);
			msh->exit_status = 1;
		}
		return (1);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (0);
}
