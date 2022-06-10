/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:44 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/09 17:20:44 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_bash	bash;

	if (ac != 1)
	{
		ft_putstr_fd("this shell does not take arguments\n", 2);
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
		if (!ft_strcmp(bash.input, "exit"))
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		if (!ft_is_just_spaces(bash.input))
		{
			ft_tokenize(&bash);
			if (!ft_check_cmd(&bash))
			{
				ft_get_args(&bash);
				ft_forking(&bash);
			}
		}
		// ft_print_pipes(&bash);
		// ft_print_envp(&bash);
		// ft_print_tokens(&bash);
		// ft_print_env(&bash, "XMODIFIERS");
		bash.first_token = ft_first_token(bash.first_token);
		ft_free_all(&bash);
	}
	return (0);
}
