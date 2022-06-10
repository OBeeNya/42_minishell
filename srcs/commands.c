/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:13:58 by hcherpre          #+#    #+#             */
/*   Updated: 2022/06/09 17:44:52 by baubigna         ###   ########.fr       */
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

int	ft_check_cmd(t_bash *bash)
{
	t_pipe	*next;
	t_token	*lst;
	int		chev;
	int		cmd;
	int		err;

	next = bash->pipes->next;
	chev = 0;
	cmd = 0;
	err = 0;
	while (next)
	{
		lst = next->first_token;
		chev = 0;
		cmd = 0;
		ft_assign_cmd(next, lst, &chev, &cmd);
		next = next->next;
	}
	if (cmd)
		err = ft_check_cmd_exec(bash);
	return (err);
}

void	ft_cmd_err(t_pipe *list)
{
	char	*temp;

	temp = ft_strjoin(list->cmd, ": command not found\n");
	ft_putstr_fd(temp, 2);
	free(temp);
}

int	ft_is_it_exec(t_bash *bash, t_pipe *list)
{
	int	i;
	int	comp;
	int	err;

	i = 0;
	comp = 0;
	err = 0;
	if (!ft_is_builtin(list->cmd))
	{
		while (bash->exec[i])
		{
			if (!ft_strcmp(list->cmd, bash->exec[i]))
			{
				comp = 1;
				break ;
			}
			i++;
		}
		if (!comp && ft_strcmp(list->cmd, "") && ft_strcmp(list->cmd, "$"))
		{
			ft_cmd_err(list);
			err++;
		}
	}
	return (err);
}

int	ft_check_cmd_exec(t_bash *bash)
{
	t_pipe	*list;
	int		err;

	err = 0;
	list = bash->pipes->next;
	while (list)
	{
		err += ft_is_it_exec(bash, list);
		list = list->next;
	}
	return (err);
}
