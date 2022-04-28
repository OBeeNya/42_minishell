/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:09:37 by hcherpre          #+#    #+#             */
/*   Updated: 2021/12/02 16:17:06 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *s1, char c)
{
	int		i;
	int		nb_word;

	i = 0;
	nb_word = 0;
	if (!(s1))
		return (0);
	while (*s1)
	{
		if (*s1 != c && nb_word == 0)
		{
			nb_word = 1;
			i++;
		}
		else if (*s1 == c)
			nb_word = 0;
		s1++;
	}
	return (i);
}

static char	*ft_word(char const *s1, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s1[start++];
	word[i] = '\0';
	return (word);
}

static char	**ft_write(char **tab, char const *s1, char c)
{
	size_t		j;
	size_t		i;
	int			index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen((char *) s1))
	{
		if (s1[i] != c && index == -1)
			index = i;
		else if ((s1[i] == c || i == ft_strlen((char *) s1)) && index >= 0)
		{
			tab[j++] = ft_word(s1, index, i);
			index = -1;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s1, char c)
{
	char	**tab;

	if (!s1 || s1 == NULL)
		return (NULL);
	tab = malloc((ft_count_word(s1, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab = ft_write(tab, s1, c);
	return (tab);
}
