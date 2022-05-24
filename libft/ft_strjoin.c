/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:45:06 by hcherpre          #+#    #+#             */
/*   Updated: 2022/05/19 10:59:39 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*final_str;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	final_str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (!final_str)
		return (NULL);
	i = 0;
	while (i < ft_strlen((char *)s1))
	{
		final_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen((char *)s2))
	{
		final_str[i++] = s2[j++];
	}
	final_str[i] = '\0';
	return (final_str);
}

char	*ft_strjoin_char(char const *s1, char c)
{
	char		*final_str;
	size_t		i;

	if (!s1)
		return (NULL);
	final_str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ 2));
	if (!final_str)
		return (NULL);
	i = 0;
	while (i < ft_strlen((char *)s1))
	{
		final_str[i] = s1[i];
		i++;
	}
	final_str[i] = c;
	final_str[i + 1] = '\0';
	return (final_str);
}
