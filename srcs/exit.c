/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:53:41 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 17:42:50 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

unsigned long long int	ft_long_atoi(const char *str)
{
	int						i;
	int						neg;
	unsigned long long int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb);
}

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
	if (ft_long_atoi(s) > 9223372036854775807)
		return (0);
	return (1);
}

void	ft_exit(t_pipe *pipe)
{
	if (pipe->args)
	{
		if (pipe->args[1])
		{
			ft_putstr_fd("minishell: exit\ntoo many arguments\n", 2);
			g_bash.err = 1;
			return ;
		}
		if (!ft_is_str_num(pipe->args[0]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(pipe->args[0], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
	}
	exit(ft_atoi(pipe->args[0]));
}
