/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:12 by hugoo             #+#    #+#             */
/*   Updated: 2022/07/09 18:50:43 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe(t_bash *bash, int i, t_pipe *pass, int k)
{
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
		k++;
		pass = pass->next;
	}
	ft_pipe_3(bash, i);
}

void	ft_pipe_2(t_pipe *pass, t_bash *bash, int i)
{
	pass->pid = fork();
	if (pass->pid == -1)
		return ;
	else if (!pass->pid)
	{
		ft_close(bash, i);
		if (pass->cmd)
		{
			if (ft_is_builtin(pass->cmd))
			{
				ft_dispatch_builtins(pass, bash);
				exit(0);
			}
			else
				ft_execute_cmd(pass, bash);
		}
		else
			exit(0);
	}
	ft_close_fds(pass);
}

void	ft_pipe_3(t_bash *bash, int i)
{
	t_pipe	*pass;

	pass = bash->pipes->next;
	if (pass->cmd && !ft_is_builtin(pass->cmd))
	{
		if (0 < waitpid(pass->pid, &bash->err, 0) && WIFEXITED(bash->err))
			bash->err = WEXITSTATUS(bash->err);
	}
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
