/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:48:42 by hcherpre          #+#    #+#             */
/*   Updated: 2022/06/03 19:36:24 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_double(char *str, size_t *i, t_bash *bash, char *final_str)
{
	if (!*i)
		final_str = ft_dbl_quotes(str, i, bash, "");
	else
		final_str = ft_dbl_quotes(str, i, bash, final_str);
	return (final_str);
}

char	*ft_single(char *str, size_t *i, char *final_str)
{
	if (!*i)
		final_str = ft_sgl_quotes(str, i, "");
	else
		final_str = ft_sgl_quotes(str, i, final_str);
	return (final_str);
}

char	*ft_dollars(char *str, size_t *i, t_bash *bash, char *final_str)
{
	char	*temp;

	if (!*i)
	{
		temp = ft_manage_doll(str, i, bash, 0);
		final_str = ft_strjoin("", temp);
		// free(temp);
	}
	else
	{
		temp = ft_manage_doll(str, i, bash, 0);
		final_str = ft_strjoin(final_str, temp);
		// free(temp);
	}
	(*i)++;
	return (final_str);
}

char	*ft_else(char *str, size_t *i, char *final_str)
{
	char	*temp;

	if (!*i)
		final_str = ft_strjoin_char("", str[*i]);
	else
	{
		temp = ft_strdup(final_str);
		free(final_str);
		final_str = ft_strjoin_char(temp, str[*i]);
		free(temp);
	}
	(*i)++;
	return (final_str);
}

char	*ft_is_quotes(char *str, t_bash *bash)
{
	size_t	i;
	char	*final_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == DBL_QT)
			final_str = ft_double(str, &i, bash, final_str);
		else if (str[i] == SGL_QT)
			final_str = ft_single(str, &i, final_str);
		else if (str[i] == '$')
			final_str = ft_dollars(str, &i, bash, final_str);
		else
			final_str = ft_else(str, &i, final_str);
	}
	return (final_str);
}
