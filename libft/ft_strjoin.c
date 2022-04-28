/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:45:06 by hcherpre          #+#    #+#             */
/*   Updated: 2021/12/01 09:45:59 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*final_str;
	size_t		i;
	size_t		j;

	if (!s1 || !2)
		return (NULL);
	final_str = malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2)));
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
