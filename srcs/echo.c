/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:01:43 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 14:36:27 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_nl_option(char *str)
{
	size_t	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_pipe *pipe)
{
	t_token	*token;
	int		nl;

	nl = 0;
	token = pipe->first_token;
	while (token->type != T_CMD)
		token = token->next;
	if (token->next)
		token = token->next;
	if (ft_is_nl_option(token->str))
	{
		while (ft_is_nl_option(token->str))
			token = token->next;
		nl++;
	}
	while (token && token->type == T_STR)
	{
		ft_putstr_fd(token->str, 1);
		if (token->next)
			ft_putstr_fd(" ", 1);
		token = token->next;
	}
	if (!nl)
		ft_putstr_fd("\n", 1);
}
