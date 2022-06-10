/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:38 by hcherpre          #+#    #+#             */
/*   Updated: 2022/06/09 16:14:17 by baubigna         ###   ########.fr       */
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

int	ft_count_quotes(char *str)
{
	size_t	i;
	size_t	j;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == SGL_QT || str[i] == DBL_QT)
		{
			j = i;
			i++;
			while (str[i] != str[j])
				i++;
			i++;
			count += 2;
		}
		else
			i++;
	}
	return (count);
}

size_t	ft_index_closing_quote(char *str, size_t i)
{
	i++;
	if (str[i - 1] == SGL_QT)
	{
		while (str[i] != SGL_QT)
			i++;
	}
	else
	{
		while (str[i] != DBL_QT)
			i++;
	}
	return (i);
}
