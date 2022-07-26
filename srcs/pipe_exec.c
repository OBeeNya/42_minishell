/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:12 by hugoo             #+#    #+#             */
/*   Updated: 2022/07/26 16:59:57 by benjamin         ###   ########.fr       */
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
	t_pipe	*pipe;

	pipe = bash->pipes->next;
	ft_close(bash, i);
	while (pipe)
	{
		waitpid(pipe->pid, &bash->err, 0);
		if (WIFSIGNALED(bash->err) && WTERMSIG(bash->err) == 2)
		{
			ft_putstr_fd("\n", 2);
			bash->err = 130;
			break ;
		}
		else if (WIFSIGNALED(bash->err) && WTERMSIG(bash->err) == 3)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			bash->err = 131;
			break ;
		}
		if (pipe->pid != -1 && (0 < waitpid(pipe->pid, &bash->err, 0))
			&& pipe->cmd_ok)
			bash->err = WEXITSTATUS(bash->err);
		ft_convert_err(bash);
		pipe = pipe->next;
	}
}

void	ft_pipe(t_bash *bash, int i, t_pipe *pass, int k)
{
	init_pipe(i, pass);
	while (pass)
	{
		if (!ft_check_cmd(bash, pass) && pass->cmd)
		{
			ft_dup_fds(pass);
			if (!k)
				dup2(pass->fd[1], pass->fdout);
			else if (k && !pass->next)
				dup2(pass->previous->fd[0], pass->fdin);
			else if (k && pass->next)
				ft_dup_middle_pipe(pass);
			ft_pipe_2(pass, bash, i);
		}
		k++;
		pass = pass->next;
	}
	ft_wait_child(bash, i);
}

void	ft_pipe_2(t_pipe *pass, t_bash *bash, int i)
{
	signal(SIGINT, SIG_IGN);
	pass->pid = fork();
	if (pass->pid == -1)
		return ;
	else if (!pass->pid)
	{
		ft_handle_signals(0);
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
