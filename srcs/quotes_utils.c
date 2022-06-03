/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:38 by hcherpre          #+#    #+#             */
/*   Updated: 2022/05/27 17:54:41 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_dbl_quotes(char *str, size_t *i, t_bash *bash, char *final_str)
{
	char		*temp;
	char		*temp2;
	size_t		j;
	size_t		len;

	j = (*i);
	len = ft_count(str, (*i));
	while ((*i) <= len)
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
	return (final_str);
}

char	*ft_sgl_quotes(char *str, size_t *i, char *final_str)
{
	char		*temp;
	size_t		len;
	size_t		k;

	len = (*i);
	k = (*i);
	k++;
	while (str[k++] != SGL_QT)
		len++;
	len++;
	while ((*i) <= len)
	{
		temp = ft_strjoin_char(final_str, str[(*i)]);
		if (*i)
			free(final_str);
		final_str = ft_strdup(temp);
		free(temp);
		(*i)++;
	}
	return (final_str);
}

int	ft_count(char *str, int i)
{
	size_t		k;
	size_t		len;

	len = i;
	k = i;
	k++;
	while (str[k++] != DBL_QT)
		len++;
	len++;
	return (len);
}
