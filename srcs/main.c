/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:44 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 17:23:34 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bash	g_bash;

int	main(int ac, char **av, char **envp)
{
	bool	first;
	bool	last;

	first = true;
	last = false;
	if (ac != 1)
	{
		ft_putstr_fd("this shell does not take arguments\n", 2);
		return (1);
	}
	(void) av;
	g_bash.err = 0;
	g_bash.echo = 0;
	ft_prompt(&g_bash, envp, first, last);
	return (0);
}
