#include "minishell.h"

size_t	check_semicolon(char **args)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen_2dim((const char **)args);
	while (i < size)
	{
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
		if (!ft_strcmp((*args)[i], "<") || !ft_strcmp((*args)[i], ">")
			|| !ft_strcmp((*args)[i], "<<") || !ft_strcmp((*args)[i], ">>"))
			i += 2;
		if (!ft_strcmp((*args)[i], "echo"))
			return (0);
		if (!ft_strcmp((*args)[i], "ls"))
			return (0);
		if (ft_iscommand(&(*args)[i]) == 1)
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
		if (!ft_strcmp(args[i++], "|"))
			pipe_count++;
	}
	return (pipe_count);
}

int	ft_iscommand(char **s)
{
	size_t	i;

	i = 0;
	if (*s == NULL || **s == '\0')
		return (-1);
	while ((*s)[i])
	{
		if (ft_isalnum((*s)[i]) == 0 && ((*s)[i] != '/' || (*s)[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_issymbol(char **s)
{
	size_t	i;

	i = 0;
	if (*s == NULL)
		return (-1);
	if (!ft_strcmp(*s, "<") || !ft_strcmp(*s, ">") || !ft_strcmp(*s, "<<")
		|| !ft_strcmp(*s, ">>") || !ft_strcmp(*s, "|") || !ft_strcmp(*s, ";"))
		return (1);
	return (0);
}
