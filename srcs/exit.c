/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:53:41 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 13:01:54 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_str_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_pipe *pipe)
{
	if (pipe->args)
	{
		if (!ft_is_str_num(pipe->args[0]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(pipe->args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
	}
	exit(ft_atoi(pipe->args[0]));
}
