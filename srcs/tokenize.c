/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:21:56 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/28 14:55:04 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_quotes(t_bash *bash)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(bash->input))
	{
		if (bash->input[i] == SGL_QT || bash->input[i] == DBL_QT)
		{
			j = i;
			i++;
			while (i < ft_strlen(bash->input))
			{
				if (bash->input[i] == bash->input[j])
					break ;
				i++;
			}
			if (i == ft_strlen(bash->input))
			{
				printf("Quotes not closed.\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	ft_tokenize_quotes(t_bash *bash)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(bash->input))
	{
		while (bash->input[i] != SGL_QT && bash->input[i] != DBL_QT)
			i++;
		if (i == 0)
		{
				
		}
	}
}

int	ft_tokenize(t_bash *bash)
{
	if (!ft_check_quotes(bash))
		return (0);
	ft_tokenize_quotes(bash);
	return (1);
}
