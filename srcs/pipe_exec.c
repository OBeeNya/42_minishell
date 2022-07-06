/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:12 by hugoo             #+#    #+#             */
/*   Updated: 2022/07/06 14:20:14 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pipe(t_bash *bash, int i, t_pipe *pass, int k)
{
	int		j;
	int		**fd;

	j = 0;
	fd = init_pipe(i);
	while (pass)
	{
		ft_dup_fds(pass);
		if (!k)
			dup2(fd[j][1], pass->fdout);
		else if (k && !pass->next)
			dup2(fd[j][0], pass->fdin);
		else if (k && pass->next)
		{
			dup2(fd[j][0], pass->fdin);
			dup2(fd[j + 1][1], pass->fdout);
		}
		ft_pipe_2(pass, bash, fd, i);
		if (k % 2 != 0)
			j++;
		k++;
		pass = pass->next;
	}
	ft_pipe_3(fd, i);
}

void	ft_pipe_2(t_pipe *pass, t_bash *bash, int **fd, int i)
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
			ft_close(fd, i);
			ft_execute_cmd(pass, bash);
		}
	}
	ft_close_fds(pass);
}

void	ft_pipe_3(int **fd, int i)
{
	ft_close(fd, i);
	ft_free_fd(fd, i);
	wait(0);
}

int	**init_pipe(int i)
{
	int		**fd;
	int		j;

	fd = ft_calloc(i, sizeof(int *));
	j = 0;
	while (j < i)
	{
		fd[j] = ft_calloc(2, sizeof(int));
		j++;
	}
	j = 0;
	while (j < i)
	{
		if (pipe(fd[j]) == -1)
			return (0);
		j++;
	}
	return (fd);
}
