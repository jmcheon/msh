#include "minishell.h"

void	handle_child_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		msh.exit_status = 130;
	}
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		msh.exit_status = 131;
	}
}

void	handle_heredoc(int signum)
{
	//printf("heredoc handle\n");
	if (signum == SIGINT)
	{
		{
			//printf("heredoc\n");
			write(STDIN_FILENO, "\n", 1);
			msh.exit_status = 130;
			close(STDIN_FILENO);
		}
	}
}

void		handle_sigint(int signum)
{
	//if (msh.g_pid > 0)
		//kill(msh.g_pid, SIGTERM);
	//write(STDERR_FILENO, "\n", 1);
	//if (msh.g_pid == -1)
		//prompt();
	if (signum == SIGINT)
	{
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDIN_FILENO, "\n", 1);
	rl_redisplay();
	msh.exit_status = 130;
	(void)signum;
	}
}

void		handle_sigquit(int signum)
{
	//printf("handle sigquit\n");
	if (msh.g_pid > 0)
	{
		kill(msh.g_pid, SIGABRT);
		write(STDERR_FILENO, "Quit: 3\n", 8);
	}
/*
	if (msh.running_heredoc == 1)
	{
		msh.running_heredoc = 0;
		printf("msh: syntax error: unexpected end of file (wanted '%s')\n", msh.heredoc_limiter);
	}
*/
	(void)signum;
}

void		listen_signals(void)
{
	signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, handle_sigquit);
	signal(SIGQUIT, SIG_IGN);
}

void		listen_signals_child(void)
{
	signal(SIGINT, handle_child_signal);
	signal(SIGQUIT, handle_child_signal);
}

void		listen_signals_heredoc(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
/*
void    sigint_handler(int sig)                                                 
{                                                                               
	((t_master *)g_msh)->sigint_signal = true;                              
	ret_value((t_master *)(g_msh), 130);                                    
	if (g_msh->commmand_running == true)                                    
	{                                                                       
		kill(g_msh->pid, sig);                                          
		write(1, "\n", 1);                                              
	}                                                                       
	else if (g_msh->heredoc_running == false)                               
	{                                                                       
		write(1, "^C", 2);                                              
		write(1, "\n", 1);                                              
		rest_struct_after_exec((t_master *)(g_msh));                    
		print_prompt((t_master *)(g_msh));                              
		((t_master *)g_msh)->sigint_signal = false;                     
	}                                                                       
	if (g_msh->heredoc_running == true)                                     
	{                                                                       
		write(1, "^C", 2);                                              
		write(1, "\n", 1);                                              
		g_msh->term->term.c_cc[VMIN] = 0;                               
		g_msh->term->term.c_cc[VTIME] = 1;                              
		tcsetattr(0, TCSANOW, &((g_msh->term)->term));                  
	}                                                                       
}
*/
