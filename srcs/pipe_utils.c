/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:23:42 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/08 15:08:02 by hcherpre         ###   ########.fr       */
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

void	ft_close(t_bash *bash, int i)
{
	int		j;
	t_pipe	*pass;

	pass = bash->pipes->next;
	j = 0;
	while (j < i)
	{
		close(pass->fd[0]);
		close(pass->fd[1]);
		pass = pass->next;
		j++;
	}
}
