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

static int	get_next_heredoc(t_minishell *msh, t_cmd *cmd, char **args, int infile)
{
	char	*line;
	int		argc;
	int		ret;

	argc = 0;
	ret = 1;
	if (!ft_strcmp(args[0], "<<"))
	{
		ft_memdel(&cmd->temp_path);
		cmd->temp_path = ft_strjoin(HEREDOC_PATH, args[1]);
		line = NULL;
		write(STDIN_FILENO, "> ", 2);
		while (ret)
		{
			ret = get_next_line(&line);
			if (!ft_strcmp(line, args[1]))
			{
				fprintf(stderr, "end of file with=%s\n", args[1]);
				ft_memdel(&line);
				break ;
			}
			argc = check_readline_argc(line);
/*
			if (argc == 0 && ret < 1)
			{
				if (execute_syntax_error(msh, args[1], -4))
				{
					fprintf(stderr, "argc, ret = (%d, %d) finished by ctrl d, %s\n", argc, ret, args[1]);
					close(infile);
					ft_memdel(&line);
					return (1);
				}
			}
*/
			write(STDIN_FILENO, "> ", 2);
			write(infile, line, ft_strlen(line));
			write(infile, "\n", 1);
			ft_memdel(&line);
		}
		close(infile);
		ft_memdel(&line);
	}
	return (0);
}

int	execute_heredoc(t_minishell *msh, t_cmd *cmd, char **args)
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
		}
		return (1);
	}
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
		}
		return (1);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (0);
}
