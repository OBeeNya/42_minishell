/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:42:27 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 13:26:10 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prompt_2(t_bash *bash)
{
	if (!ft_is_just_spaces(bash->input))
	{
		if (ft_tokenize(bash))
		{
			if (!ft_check_cmd(bash))
			{
				ft_get_args(bash);
				if (!ft_update_fds(bash))
					ft_forking(bash);
			}
		}
	}
}

void	ft_prompt(t_bash *bash, char **envp, bool first, bool last)
{
	while (1)
	{
		bash->echo = 0;
		ft_initialize_bash(bash, envp, first);
		first = false;
		signal(SIGINT, ctrl_handler);
		signal(SIGSEGV, ctrl_handler);
		signal(SIGQUIT, SIG_IGN);
		bash->input = readline("minishell ~ ");
		if (!bash->input)
			exit(0);
		add_history(bash->input);
		ft_prompt_2(bash);
		bash->first_token = ft_first_token(bash->first_token);
		ft_free_all(bash, last);
	}
	last = true;
	ft_free_all(bash, last);
}
