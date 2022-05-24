/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:26:44 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/24 15:28:34 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tokens(t_bash *bash)
{
	t_token	*print;

	print = ft_first_token(bash);
	while (print)
	{
		printf("TOKEN: %s TOKEN TYPE: %c\n", print->str, print->type);
		print = print->next;
	}
}

void	ft_print_env(t_bash *bash, char *key)
{
	t_env	*print;

	print = bash->env;
	while (ft_strcmp(print->key, key))
		print = print->next;
	if (print)
		printf("%s\n", print->string);
}

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
//		builtins(input);
		if (!ft_strcmp(bash.input, "exit"))
		{
			ft_putstr_fd("exit\n", 1);
			exit(1);
		}
		if (!ft_is_just_spaces(bash.input))
			ft_tokenize(&bash);
		ft_print_tokens(&bash);
		bash.first_token = ft_first_token(&bash);
		// ft_print_env(&bash, "XMODIFIERS");
		ft_free_all(&bash);
	}
	return (0);
}
