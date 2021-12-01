#include "minishell.h"

size_t    ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t    i;
	size_t    j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i != size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

size_t    ft_tabsize(char **tab)
{
	size_t    size;

	size = 0;
	while (tab[size])
		++size;
	return (size);
}

int     ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
static int line_in_env(char *cmd, char **envp)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(cmd);

	while (envp[++i])
	{
		if (ft_strncmp(envp[i], cmd, len) == 0 
				&& (envp[i][len] == '=' || !envp[i][len]))
			return (i);
	}
	return (-1);
}

char     *ft_getvar_old(char *str)
{
    int    i;

    i = 0;
    if (!str)
        return (NULL);
    while (str[i] && str[i] != '+' && str[i] != '=')
        i++;
    str[i] = 0;
    return (str);
}

char     *ft_getvar(char *str)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = NULL;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (i <= 0)
		return (NULL);
	temp = ft_strdup_by_index(str, 0, i - 1);
	//printf("getvar str:%s\n", str);
	//printf("getvar temp:%s\n", temp);
/*
	ft_memdel(&temp);
	return (str);
*/
	return (temp);
	//return (ft_strdup_by_index(str, 0, i - 1));
}

int     ft_checkvar(char *str)
{
	int i;

	if (!str)
		return (0);
	if (!str[0])
		return (0);
	if (str[0] && ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	i = -1;
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
	}
	return (1);
}

int     ft_check_syntax(char *str)
{
	int i;

	while (*str && *str != '+' && *str != '=')
		str++;
	//printf("checkvar str:%s\n", str);
	if ((*str == '+' && *(str + 1) == '='))
	{
	//	printf("+= checkvar str:%s\n", str);
		return (1);
	}
	if (*str == '=')
	{
	//	printf("= checkvar str:%s\n", str);
		return (1);
	}
	if (*str == '\0')
		return (1);
	return (0);
}

size_t    ft_strlcat_new(char *dst, const char *src, size_t size)
{
	size_t    i;
	size_t    j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && i + j + 1 < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i != size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}


void            ft_setenv(t_minishell *msh, char **args, char *new_path, char *variable, char *value, int mode, char **envp[])
{
	char	**temp_args;
	char	*temp;
	char	*temp2;
	int    n;

	temp = NULL;
	temp2 = NULL;
	temp_args = NULL;
	//printf("ft_setenv value:%s$\n", value);
	n = search_one_variable_path(msh, variable);
	if (n >= 0)
	{
	//	printf("n=%d, envp[%d]=%s\n", n, n, msh->envp[n]);
		if (mode == 1)
		{
			temp = msh->envp[n];
			msh->envp[n] = ft_strjoin(msh->envp[n], value);
			ft_memdel(&temp);
		}
		else
		{
			temp = msh->envp[n];
			msh->envp[n] = ft_strjoin_memdel(ft_strdup(variable), ft_strjoin("=", value));
			ft_memdel(&temp);
		}

	}
	else
	{
		temp = ft_strdup(new_path);
		temp_args = malloc_args(temp);
		msh->envp = ft_strjoin_2dim_memdel(msh->envp, temp_args);
		ft_memdel(&temp);
	}
	ft_memdel(&temp);
	ft_memdel(&temp2);
}

void        ft_export(t_minishell *msh, char **cmd)
{
	int i;
	int len;
	int mode;
	char *variable;

	i = 0;
	variable = NULL;
	if (!cmd[1])
	{
		while (msh->envp[i])
			printf("declare -x %s\n", msh->envp[i++]);
		return ;
	}
	while (cmd[++i])
	{
		variable = ft_getvar(cmd[i]);
		//printf("af getvar var:%s\n", variable);
		if (ft_checkvar(variable) == 0 || ft_check_syntax(cmd[i]) == 0)
		{
			//printf("export: `%s': not a valid identifier\n", cmd[i]);
			msh->exit_status = 1;
		}
		else
		{
			if (ft_strcmp(variable, cmd[i]))
			{
				//printf("42\n");
				len = ft_strlen(variable);
				//printf("cmd[i] + len:%s$\n", cmd[i] + len);
				mode = (cmd[i][len] == '+' && cmd[i][len + 1] == '=');
				//printf("mode=%d\n", mode);
				//if (mode == 1)
					//printf("value=%s$\n", cmd[i] + len + 1 + mode);
				ft_setenv(msh, cmd, cmd[i], variable, cmd[i] + len + 1 + mode, mode, &msh->envp);
			}
		}
	}
	ft_memdel(&variable);
	//printf("finish ft_export\n");
	msh->exit_status = 0;
}
