/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:44 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/28 14:53:21 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_bash	bash;

	if (ac != 1)
	{
		printf("Don't give any arguments.\n");
		return (1);
	}
	(void) av;
	ft_initialize_bash(&bash, envp);
	while (1)
	{
		signal(SIGINT, ctrl_handler);
		signal(SIGSEGV, ctrl_handler);
		signal(SIGQUIT, SIG_IGN);
		bash.input = readline(">> ");
		add_history(bash.input);
//		builtins(input);
		if (!ft_strcmp(bash.input, "exit"))
			exit(0);
		ft_tokenize(&bash);
		free(bash.input);
	}
	return (0);
}
