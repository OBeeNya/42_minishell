/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:27:54 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 18:33:12 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_err_echo_dir(t_pipe *pipe, t_bash *bash)
{
	t_token	*token;

	if (pipe->fdout == -1)
	{
		token = pipe->first_token;
		while (token && token->type != T_APPEND && token->type != T_OUTPUT)
			token = token->next;
		if (token)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(token->str, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			bash->err = 1;
			bash->echo = 1;
			return (1);
		}
	}
	return (0);
}

int	ft_check_export(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (str[i] != '_' && str[i] != '=' && str[i] != '+'
			&& !ft_isalpha(str[i]))
			return (1);
		i++;
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (1);
	return (0);
}

void	ft_clean_err(t_bash *bash)
{
	t_pipe	*pipe;

	pipe = bash->pipes->next;
	while (pipe)
	{
		if (pipe->cmd && !ft_strncmp(pipe->cmd, "echo", 4)
			&& !bash->echo && !pipe->next)
			bash->err = 0;
		pipe = pipe->next;
	}
}

void	ft_err_no_exec(char *cmd, t_bash *bash)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	bash->err = 127;
}

void	ft_fd_in_err_no(t_token *token, t_bash *bash)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	bash->err = 1;
}
