/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:42:27 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/26 16:40:36 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

void	ft_heredoc_loop(char *unquoted, int quotes, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			ft_eof_heredoc(unquoted);
		line = ft_expand_heredoc(line, &g_bash, quotes);
		if (!ft_strcmp(line, unquoted))
			break ;
		write(fd, line, ft_strlen(line) * sizeof(char));
		write(fd, "\n", 1);
		free(line);
	}
}

void	ft_prompt_2(t_bash *bash)
{
	if (!ft_is_just_spaces(bash->input))
	{
		if (ft_tokenize(bash))
		{
			if (!ft_update_fds(bash))
				ft_forking(bash);
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
		ft_handle_signals(0);
		bash->input = readline("minishell ~ ");
		if (!bash->input)
		{
			bash->err = 1;
			ft_free_all(bash, true);
		}
		if (ft_strcmp(bash->input, ""))
			add_history(bash->input);
		ft_prompt_2(bash);
		bash->first_token = ft_first_token(bash->first_token);
		ft_free_all(bash, last);
	}
	last = true;
	ft_free_all(bash, last);
}
