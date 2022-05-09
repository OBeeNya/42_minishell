/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:44 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/05 18:26:41 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_bash	bash;
	int		i;

	if (ac != 1)
	{
		ft_putstr_fd("this shell does not execute files\n", 2);
		return (1);
	}
	(void) av;
	while (1)
	{
		ft_initialize_bash(&bash, envp);
		signal(SIGINT, ctrl_handler);
		signal(SIGSEGV, ctrl_handler);
		signal(SIGQUIT, SIG_IGN);
		bash.input = readline("minishell ~ ");
		add_history(bash.input);
//		builtins(input);
		if (!ft_strcmp(bash.input, "exit"))
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		i = 0;
		while (bash.input[i])
		{
			if (bash.input[i])
			{
				ft_tokenize(&bash);
				break ;
			}
			i++;
		}
		ft_print_tokens(&bash);
//		ft_free_all(&bash);
//		free(bash.input);
	}
	return (0);
}
