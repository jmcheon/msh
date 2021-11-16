#include "minishell.h"

static int	open_outfile(char *token, char *outfile_path, int *outfile)
{
	if (!ft_strcmp(token, ">>"))
		*outfile = open(outfile_path, O_RDWR | O_CREAT | O_APPEND, 0664);
	else
		*outfile = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*outfile == -1)
		return (1);
	return (0);
}

int	redirect_output(t_minishell *msh, char *token, char *outfile_path)
{
	char	*temp;
	int		outfile;

	temp = NULL;
	if (open_outfile(token, outfile_path, &outfile) == 1)
	{
		if (msh->ret == NULL)
		{
			temp = ft_strjoin(outfile_path, ": ");
			msh->ret = ft_strjoin(temp, strerror(errno));
			ft_memdel(&temp);
		}
		return (1);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	return (0);
}
