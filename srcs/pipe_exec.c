/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:12 by hugoo             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/28 17:08:12 by benjamin         ###   ########.fr       */
=======
/*   Updated: 2022/07/26 17:36:25 by benjamin         ###   ########.fr       */
>>>>>>> 81778941ff90b564dbec9072d82aa6baabc4382b
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup_middle_pipe(t_pipe *pass)
{
	dup2(pass->previous->fd[0], pass->fdin);
	dup2(pass->fd[1], pass->fdout);
}

<<<<<<< HEAD
void	ft_wait_child(t_bash *b, int i, int j)
{
	t_pipe	*pipe;

	pipe = b->pipes->next;
	while (pipe)
	{
		waitpid(pipe->pid, &b->err, 0);
		if ((j - 1 == i) && WIFSIGNALED(b->err)
			&& WTERMSIG(b->err) == 2)
		{
			ft_norme_pipe_1(b);
			break ;
		}
		else if ((j - 1 == i) && WIFSIGNALED(b->err) && WTERMSIG(b->err) == 3)
		{
			if (i)
				break ;
			ft_norme_pipe_2(b);
			break ;
		}
		if (pipe->pid != -1 && (0 < waitpid(pipe->pid, &b->err, 0))
			&& pipe->cmd_ok)
			b->err = WEXITSTATUS(b->err);
		ft_convert_err(b);
=======
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
>>>>>>> 81778941ff90b564dbec9072d82aa6baabc4382b
		pipe = pipe->next;
	}
}

void	ft_pipe(t_bash *bash, int i, t_pipe *pass, int k)
{
	int	j;

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
			ft_pipe_2(pass, bash, i);
		}
		else
			pass->cmd_ok = 2;
		k++;
		pass = pass->next;
	}
<<<<<<< HEAD
	ft_close(bash, i);
	ft_wait_child(bash, i, j);
=======
	if (j - 1 == i)
		ft_wait_child(bash, i);
>>>>>>> 81778941ff90b564dbec9072d82aa6baabc4382b
}

void	ft_pipe_2(t_pipe *pass, t_bash *bash, int i)
{
<<<<<<< HEAD
	if (!ft_strcmp(pass->cmd, "env") || !ft_strcmp(pass->cmd, "export")
		|| !ft_strcmp(pass->cmd, "unset"))
	{
		if (bash->err == 127)
			bash->err = 0;
		ft_dispatch_builtins(pass, bash);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		pass->pid = fork();
		if (pass->pid == -1)
			return ;
		else if (!pass->pid)
			ft_fork_pipe(bash, i, pass);
	}
=======
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
>>>>>>> 81778941ff90b564dbec9072d82aa6baabc4382b
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
