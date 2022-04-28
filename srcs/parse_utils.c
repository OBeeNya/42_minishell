/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:09:08 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/27 13:28:52 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_trim(char *s)
{
	int		i;
	int		j;
	char	*t;

	i = 0;
	while (s[i] == 32)
		i++;
	j = ft_strlen(s);
	while (s[j] == 32)
		j--;
	t = malloc(sizeof(char) * (j - i + 1));
	while (i < j)
	{
		t[i] = s[i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
