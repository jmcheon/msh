#include "minishell.h"

size_t	check_semicolon(char **args)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)args);
	while (i < size)
	{
		fprintf(stderr, "check semicolon=%s\n", args[i]);
		if (!ft_strcmp(args[i], ";"))
			return (i + 1);
		i++;
	}
	return (0);
}

size_t	check_command(char ***args)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)*args);
	while (i < size)
	{
		if (check_semicolon((*args) + i) != 0)
			i = check_semicolon((*args) + i);
		fprintf(stderr, "check command=%s\n", (*args)[i]);
		if (!ft_strcmp((*args)[i], "<") || !ft_strcmp((*args)[i], ">")
			|| !ft_strcmp((*args)[i], "<<") || !ft_strcmp((*args)[i], ">>"))
			i += 2;
	//	printf("check command *args + i=%s\n", *(*args + i));
		if (ft_iscommand(&(*args)[i]) == 1)
		//if (ft_isalnum((*args)[i]) == 0 && (*args)[i] != '_' && (*args)[i] != '/')
			return (1);
		i++;
	}
	return (0);
}

size_t	check_redirection_input(char **args)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)args);
	while (i < size)
	{
		if (!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

size_t	check_redirection_heredoc(char **args)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)args);
	while (i < size)
	{
		if (!ft_strcmp(args[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

size_t	check_pipe_count(char **args, size_t size)
{
	size_t	i;
	size_t	pipe_count;

	i = 0;
	pipe_count = 0;
	if (size == -1)
		size = ft_strlen_2dim((const char **)args);
	while (i < size)
	{
		//if (ft_strchr(args[i++], '|'))
		if (!ft_strcmp(args[i++], "|"))
			pipe_count++;
	}
	return (pipe_count);
}

int	execute_syntax_error(t_minishell *msh, char *s, int i)
{
	pid_t	pid;
	char	**pipe_args;
	char	*temp;
	int	wstatus;

	wstatus = 0;
	printf("i=%d\n", i);
	//printf("check syntax error\n");
	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return (1);
	}
	if (pid == 0)
	{
		//if (msh->ret != NULL)
			ft_memdel(&msh->ret);
		if (i == -2)
			msh->ret = ft_strjoin("msh: ", "syntax error: unexpected end of file");
		else if (i == -3)
			msh->ret = ft_strjoin("msh: ", "syntax error: unexpected token 'new line'");
		else if (i == -4)
		{
			temp = ft_strjoin(s, ")");
			msh->ret = ft_strjoin("msh: syntax error: unexpected end of file (wanted ", temp);
			ft_memdel(&temp);
		}
		else if (i == -5)
			msh->ret = ft_strjoin("msh: unexpected EOF while looking for matching ", s);
		else
			msh->ret = ft_strjoin("msh: syntax error near unexpected token ", s);
		return (1);
	}
	wait(&wstatus);
	if (WEXITSTATUS(wstatus))
		return (1);
	return (0);
}
/*
int	ft_iscommand(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (2);
	while (*s)
	{
		if (ft_isalnum(*s) == 0 && *s != '_' && *s != '/')
			return (0);
		s++;
	} 
	return (1);
}
*/

int	ft_iscommand(char **s)
{
	size_t	i;

	i = 0;
	fprintf(stderr, "ft_iscommand str=%s\n", *s);
	if (*s == NULL || **s == '\0')
		return (-1);
	while ((*s)[i])
	{
		if (ft_isalnum((*s)[i]) == 0 && ((*s)[i] != '/' || (*s)[i] != '_'))
			return (0);
		i++;
		//s++;
	} 
	return (1);
}

int	ft_issymbol(char **s)
{
	size_t	i;

	i = 0;
	if (*s == NULL)
		return (-1);
	if (!ft_strcmp(*s, "<") || !ft_strcmp(*s, ">") || !ft_strcmp(*s, "<<") || !ft_strcmp(*s, ">>") || !ft_strcmp(*s, "|"))
		return (1);
	return (0);
}
int	check_syntax_error(t_minishell *msh, char **args, size_t size)
{
	size_t	i;
	int	err;

	i = 0;
	err = 0;
	while (i < size)
	{
/*
		if (!ft_strcmp(args[i], "|"))// || (!ft_strcmp(args[i], "|") && !ft_strcmp(args[i - 1], "|")))
		{
			if (i == 0 || (i > 0 && !ft_iscommand(args[i - 1])))
				execute_syntax_error(msh, "'|'", -1);
			ft_memdel_2dim(&args);
			return (1);
		}
*/
		if ((!ft_strcmp(args[0], ";") || (!ft_strcmp(args[i], ";") && !ft_strcmp(args[i - 1], ";")))
			|| (!ft_strcmp(args[i], ";") && !ft_strcmp(args[i + 1], ";")))
		//if (!ft_strcmp(args[0], "|") || (!ft_strcmp(args[size - 1], "|") && !ft_strcmp(args[size - 2], "|")))
		{
			if (execute_syntax_error(msh, "';'", -1) == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
		if ((!ft_strcmp(args[0], "|") || (!ft_strcmp(args[i], "|") && !ft_strcmp(args[i - 1], "|")))
			|| (!ft_strcmp(args[i], "|") && !ft_strcmp(args[i + 1], "|")))
		//if (!ft_strcmp(args[0], "|") || (!ft_strcmp(args[size - 1], "|") && !ft_strcmp(args[size - 2], "|")))
		{
			if (execute_syntax_error(msh, "'|'", -1) == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
		//if ((ft_iscommand(args[i])))
		//	printf("args[i]=%s\n", args[i]);
		//if (ft_strcmp(args[i], "<"))
		//	printf("< args[i]=%s\n", args[i]);
		if ((!ft_strcmp(args[i], "<<")) || (!ft_strcmp(args[i], "<"))
			|| (!ft_strcmp(args[i], ">")) || (!ft_strcmp(args[i], ">>")))
		{
			if (ft_issymbol(&args[i + 1]) == 1)
				err = execute_syntax_error(msh, args[i + 1], -1);
			else if ((args[i + 1]) == NULL)
				err = execute_syntax_error(msh, args[i], -3);
			if (err == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
/*
		if (!ft_strcmp(args[i], "<<"))
		{
			if (!ft_isfile(args[i + 1]))
				err = execute_syntax_error(msh, args[i + 1], -1);
			else if ((args[i + 1]) == NULL)
				err = execute_syntax_error(msh, "'<<'", -3);
			if (err == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}

		if (!ft_strcmp(args[i], "<"))
		{
			if (!ft_isfile(args[i + 1]))
				err = execute_syntax_error(msh, args[i + 1], -1);
			else if ((args[i + 1]) == NULL)
				err = execute_syntax_error(msh, "'<'", -3);
			if (err == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
		if (!ft_strcmp(args[i], ">"))
		{
			if (!ft_isfile(args[i + 1]))
				err = execute_syntax_error(msh, args[i + 1], -1);
			else if ((args[i + 1]) == NULL)
				err = execute_syntax_error(msh, "'>'", -3);
			if (err == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
		if (!ft_strcmp(args[i], ">>"))
		{
			if (!ft_isfile(args[i + 1]))
				err = execute_syntax_error(msh, args[i + 1], -1);
			else if ((args[i + 1]) == NULL)
				err = execute_syntax_error(msh, "'>>'", -3);
			if (err == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
*/
		i++;
	}
	return (0);
}
int	check_readline_syntax_error(t_minishell *msh, char *line)
{
	t_flags	flags;
	char	*temp;
	char	**args;
	size_t	i;
	int	err;

	i = 0;
	err = 0;
	init_flags(&flags);
	check_quote_characters(&flags, line);
	if (flags.q_single == 1)
		temp = ft_strjoin(line, "\'");
	else if (flags.q_double == 1)
		temp = ft_strjoin(line, "\"");
	else
		temp = ft_strdup(line);
	fprintf(stderr, "check syntax readline new line=%s\n", temp);
	args = split_readline_by_argc(msh, temp);
	ft_memdel(&temp);
	if (check_syntax_error(msh, args, ft_strlen_2dim((const char **)args)) == 1)
	{
	//	ft_memdel_2dim(&args);
		return (1);
	}

/*
	while (line[i] != '\0')
	{
		if (line[0] == ';' || (line[i] == ';' && line[i - 1] == ';')
			|| (line[i] == ';' && line[i + 1] == ';'))
		{
			if (execute_syntax_error(msh, "';'", -1) == 1)
				return (1);
		}
		if (line[0] == '|' || (line[i] == '|' && line[i - 1] == '|')
			|| (line[i] == '|' && line[i + 1] == '|'))
		{
			if (execute_syntax_error(msh, "'|'", -1) == 1)
				return (1);
		}
		if ((!ft_strcmp(args[i], "<<")) || (!ft_strcmp(args[i], "<"))
			|| (!ft_strcmp(args[i], ">")) || (!ft_strcmp(args[i], ">>")))
		{
			if (ft_issymbol(&args[i + 1]) == 1)
				err = execute_syntax_error(msh, args[i + 1], -1);
			else if ((args[i + 1]) == NULL)
				err = execute_syntax_error(msh, args[i], -3);
			if (err == 1)
			{
				ft_memdel_2dim(&args);
				return (1);
			}
		}
		i++;
	}
*/
	ft_memdel_2dim(&args);
	return (0);
}
