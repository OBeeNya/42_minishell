/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:09:08 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/04 17:40:26 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_token_sep(t_token *token)
{
	if (token->type == T_RED_I_SGL || token->type == T_RED_I_DBL
		|| token->type == T_RED_O_SGL || token->type == T_RED_I_SGL)
		return (1);
	return (0);
}

char	*ft_cpy_from_input(t_bash *bash, size_t i, size_t j)
{
	char	*cpy;
	size_t	c;

	c = 0;
	cpy = malloc(sizeof(char) * (i - j + 1));
	if (cpy)
	{
		while (j + c < i)
		{
			cpy[c] = bash->input[j + c];
			c++;
		}
		cpy[c] = '\0';
	}
	return (cpy);
}
