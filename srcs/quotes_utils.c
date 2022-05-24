/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:38 by hcherpre          #+#    #+#             */
/*   Updated: 2022/05/24 15:17:51 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_dbl_quotes(char *str, size_t *i, t_bash *bash, char *final_str)
{
	char	*temp;
	char	*temp2;
	size_t	j;

	j = *i;
	(*i)++;
	while (str[(*i)] != DBL_QT)
	{
		if (str[(*i)] == '$')
		{
			temp2 = ft_manage_doll(str, i, bash, 1);
			temp = ft_strjoin(final_str, temp2);
			free(temp2);
		}
		else
			temp = ft_strjoin_char(final_str, str[(*i)]);
		if (j)
			free(final_str);
		final_str = ft_strdup(temp);
		free(temp);
		(*i)++;
	}
	(*i)++;
	return (final_str);
}

char	*ft_sgl_quotes(char *str, size_t *i, char *final_str)
{
	char	*temp;

	(*i)++;
	while (str[(*i)] != SGL_QT)
	{
		temp = ft_strjoin_char(final_str, str[(*i)]);
		if (*i - 1)
			free(final_str);
		final_str = ft_strdup(temp);
		free(temp);
		(*i)++;
	}
	(*i)++;
	return (final_str);
}
