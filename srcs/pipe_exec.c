/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:12 by hugoo             #+#    #+#             */
/*   Updated: 2022/07/08 12:57:09 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe(t_bash *bash, int i, t_pipe *pass, int k)
{
	int		j;

	j = 0;
	init_pipe(i, pass);
	while (pass)
	{
		ft_dup_fds(pass);
		if (!k)
			dup2(pass->fd[1], pass->fdout);
		else if (k && !pass->next)
			dup2(pass->previous->fd[0], pass->fdin);
		else if (k && pass->next)
		{
			dup2(pass->previous->fd[0], pass->fdin);
			dup2(pass->fd[1], pass->fdout);
		}
		ft_pipe_2(pass, bash, i);
		if (k % 2 != 0)
			j++;
		k++;
		pass = pass->next;
	}
	ft_pipe_3(bash, i);
}

void	ft_pipe_2(t_pipe *pass, t_bash *bash, int i)
{
	pid_t	pid;

	if (ft_is_builtin(pass->cmd))
		ft_dispatch_builtins(pass, bash);
	else
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (!pid)
		{
			ft_close(bash, i);
			ft_execute_cmd(pass, bash);
		}
	}
	ft_close_fds(pass);
}

void	ft_pipe_3(t_bash *bash, int i)
{
	ft_close(bash, i);
	wait(0);
}

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
