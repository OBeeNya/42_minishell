/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:23:42 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/09 18:54:48 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_assign_cmd(t_pipe *next, t_token *lst, int *chev, int *cmd)
{
	while (lst)
	{
		if ((!lst->previous) && lst->type == T_STR)
		{
			lst->type = T_CMD;
			next->cmd = ft_strdup(lst->str);
			*cmd = 1;
		}
		else if ((!lst->previous) && lst->type != T_STR)
			*chev = 1;
		else if (*chev == 1 && lst->previous->type == T_STR && \
			lst->previous->previous->type != T_STR && lst->type == T_STR)
		{
			lst->type = T_CMD;
			next->cmd = ft_strdup(lst->str);
			*cmd = 1;
		}
		lst = lst->next;
	}
}

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
