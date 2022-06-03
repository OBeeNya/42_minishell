/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:23:20 by hcherpre          #+#    #+#             */
/*   Updated: 2022/05/26 14:38:00 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_manage_doll(char *str, size_t *i, t_bash *bash, int qt)
{
	char	*temp;

	if ((*i) < ft_strlen(str))
	{
		if ((((*i) > 0 && str[*i - 1] == DBL_QT) || \
			((*i) > 0 && str[*i - 1] == SGL_QT)) && \
			(str[*i + 1] == DBL_QT || str[*i + 1] == SGL_QT) && qt)
		{
			temp = ft_strjoin_char("", str[*i]);
			return (temp);
		}
		else if ((((*i) > 0 && str[*i - 1] == DBL_QT) || \
			((*i) > 0 && str[*i - 1] == SGL_QT)) && \
			(str[*i + 1] == DBL_QT || str[*i + 1] == SGL_QT) && !qt)
			return ("");
		else if (str[*i + 1] == 32 || str[*i + 1] == '\0' \
			|| (str[*i + 1] >= 0 && str[*i + 1] < 48) \
			|| (str[*i + 1] > 57 && str[*i + 1] < 65) \
			|| (str[*i + 1] > 90 && str[*i + 1] < 95) \
			|| str[*i + 1] > 122 || str[*i + 1] == 96)
			return ("$");
		else
			return (ft_manage_doll_2(str, i, bash));
	}
	return (NULL);
}

char	*ft_manage_doll_2(char *str, size_t *i, t_bash *bash)
{
	size_t	k;
	char	*temp;
	char	*final_str;

	(*i)++;
	k = (*i);
	while ((str[k] && str[k] != '$') && ((str[k] >= 48 && str[k] <= 57)
			|| (str[k] >= 65 && str[k] <= 90)
			|| (str[k] >= 97 && str[k] <= 122) || str[k] == 95))
		k++;
	temp = ft_strndup(str, (*i), (k - (*i)));
	(*i) = k - 1;
	if (!ft_is_var(bash, temp))
		final_str = ft_strdup("");
	else
		final_str = ft_strdup(ft_is_var(bash, temp));
	free(temp);
	return (final_str);
}

char	*ft_is_var(t_bash *bash, char *str)
{
	t_env	*var;

	var = bash->env;
	while (var)
	{
		if (!ft_strcmp(var->key, str))
			return (var->string);
		var = var->next;
	}
	return (NULL);
}

void	ft_quotes_doll(t_bash *bash)
{
	char	*temp;
	char	*temp2;

	temp = ft_is_quotes(bash->input, bash);
	free(bash->input);
	temp2 = ft_strdup(temp);
	free(temp);
	bash->input = ft_strtrim(temp2, " ");
	free(temp2);
}
