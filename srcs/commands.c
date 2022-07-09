/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:13:58 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/09 14:50:16 by baubigna         ###   ########.fr       */
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
	{
		ft_executable(bash);
		err = ft_check_cmd_exec(bash);
		return (err);
	}
	return (1);
}

void	ft_cmd_err(t_pipe *list, t_bash *bash)
{
	char	*temp;

	if (!ft_strcmp("..", list->cmd))
	{
		ft_putstr_fd(list->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		bash->err = 127;
	}
	else if (list->cmd[0] != '.' && list->cmd[0] != '/')
	{
		temp = ft_strjoin(list->cmd, ": command not found\n");
		ft_putstr_fd(temp, 2);
		free(temp);
		bash->err = 127;
	}
}

int	ft_is_it_exec(t_bash *bash, t_pipe *list)
{
	int	comp;
	int	err;

	comp = 0;
	err = 0;
	if (list->cmd[0] == '/')
		return (err);
	if (!ft_is_builtin(list->cmd))
	{
		if (bash->exec)
			ft_check_exec(bash, list, &comp, &err);
		else
		{
			ft_cmd_err(list, bash);
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
