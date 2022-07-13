/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:36:01 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/13 19:46:32 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

void	ctrl_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\nminishell ~ ", 1);
		g_bash.err = 130;
	}
	else if (signum == SIGSEGV)
	{
		ft_free_all(&g_bash, true);
		ft_putstr_fd("exit\n", 1);
		exit(1);
	}
}
