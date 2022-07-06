/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:44 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/06 14:37:10 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_bash	bash;
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
	bash.err = 0;
	while (1)
	{
		ft_initialize_bash(&bash, envp, first);
		first = false;
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
		if (!ft_strcmp(bash.input, "$?"))
			printf("errno: %d\n", bash.err);
		if (!ft_is_just_spaces(bash.input))
		{
			if (ft_tokenize(&bash))
			{
				if (!ft_check_cmd(&bash))
				{
					ft_get_args(&bash);
					if (!ft_update_fds(&bash))
						ft_forking(&bash);
				}
				else
					ft_executable(&bash);
			}
		}
		bash.first_token = ft_first_token(bash.first_token);
		ft_free_all(&bash, last);
	}
	last = true;
	ft_free_all(&bash, last);
	return (0);
}
