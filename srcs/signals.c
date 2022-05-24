/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 15:36:01 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/18 16:56:04 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrl_handler(int signum)
{
	if (signum == SIGINT)
		printf("\nminishell ~ ");
	else if (signum == SIGSEGV)
	{
		ft_putstr_fd("exit\n", 1);
		exit(1);
	}
}
