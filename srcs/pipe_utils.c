/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:23:42 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/04 17:25:56 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	nb_pipes(t_pipe *pass)
{
	int	i;

	i = 0;
	while (pass->next)
	{
		i++;
		pass = pass->next;
	}
	return (i);
}

void	ft_close(int **fd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	ft_free_fd(int **fd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(fd[j]);
		j++;
	}
	free(fd);
}
