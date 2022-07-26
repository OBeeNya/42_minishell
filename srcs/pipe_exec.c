/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:12 by hugoo             #+#    #+#             */
/*   Updated: 2022/07/26 11:36:38 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup_middle_pipe(t_pipe *pass)
{
	dup2(pass->previous->fd[0], pass->fdin);
	dup2(pass->fd[1], pass->fdout);
}

void	ft_wait_child(t_bash *bash, int i)
{
	int		status;
	t_pipe	*pipe;

	pipe = bash->pipes->next;
	status = 0;
	ft_close(bash, i);
	while (pipe)
	{
		if (pipe->pid != -1 && (0 < waitpid(pipe->pid, &status, 0)))
		{
			bash->err = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == 2)
				{
					bash->err = 130;
					ft_putstr_fd("\n", 1);
				}
				else if (WTERMSIG(status) == 3)
				{
					ft_putstr_fd("Quit (core dumped)\n", 2);
					bash->err = 131;
				}
			}
		}
		pipe = pipe->next;
	}
}

void	ft_pipe(t_bash *bash, int i, t_pipe *pass, int k)
{
	pid_t	pid;
	int		j;

	j = 0;
	init_pipe(i, pass);
	while (pass)
	{
		if (!ft_check_cmd(bash, pass) && pass->cmd)
		{
			j++;
			ft_dup_fds(pass);
			if (!k)
				dup2(pass->fd[1], pass->fdout);
			else if (k && !pass->next)
				dup2(pass->previous->fd[0], pass->fdin);
			else if (k && pass->next)
				ft_dup_middle_pipe(pass);
			pid = ft_pipe_2(pass, bash, i);
		}
		k++;
		pass = pass->next;
	}
	(void)pid;
	// if (j - 1 == i)
		// ft_pipe_3(bash, i, pid);
		ft_wait_child(bash, i);
}

pid_t	ft_pipe_2(t_pipe *pass, t_bash *bash, int i)
{
	signal(SIGINT, SIG_IGN);
	pass->pid = fork();
	if (pass->pid == -1)
		return (pass->pid);
	else if (!pass->pid)
	{
		ft_handle_signals();
		ft_close(bash, i);
		ft_get_args(bash);
		if (ft_is_builtin(pass->cmd))
		{
			ft_dispatch_builtins(pass, bash);
			ft_free_all(bash, false);
			ft_free_env(bash);
			ft_close_int_fd();
			exit(bash->err);
		}
		else if (pass->cmd)
			ft_execute_cmd(pass, bash);
	}
	if (pass->cmd)
		ft_close_fds(pass);
	return (pass->pid);
}

// void	ft_pipe_3(t_bash *bash, int i, pid_t pid)
// {
// 	int		j;

// 	j = 0;
// 	ft_close(bash, i);
// 	while (j < i)
// 	{
// 		if (0 < waitpid(pid, &bash->err, 0) && WIFEXITED(bash->err))
// 			bash->err = WEXITSTATUS(bash->err);
// 		j++;
// 	}
// }

void	init_pipe(int i, t_pipe *pass)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (pipe(pass->fd) == -1)
			return ;
		pass = pass->next;
		j++;
	}
}
