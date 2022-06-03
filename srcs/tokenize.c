/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:21:56 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/03 18:34:07 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_gather_trim(t_bash *bash, char *trim, size_t j, size_t k)
{
	size_t	l;

	l = k;
	while (1)
	{
		while (trim[l] && trim[l] != SGL_QT && trim[l] != DBL_QT
			&& trim[l] != RED_I && trim[l] != RED_O && trim[l] != PIPE)
			l++;
		if (trim[l] == SGL_QT || trim[l] == DBL_QT)
			l = ft_ignore_quotes(trim, l);
		if (trim[l] == PIPE || trim[l] == RED_I || trim[l] == RED_O
			|| l == ft_strlen(trim))
			break ;
	}
	ft_new_token(bash, j + k, j + l);
	return (l);
}

void	ft_token_separators(t_bash *bash, char *trim, size_t j)
{
	size_t	k;

	k = 0;
	while (k < ft_strlen(trim))
	{
		if ((trim[k] == RED_I && trim[k + 1] == RED_I)
			|| (trim[k] == RED_O && trim[k + 1] == RED_O))
		{
			ft_new_token(bash, j + k, j + k + 2);
			k += 2;
		}
		else if (trim[k] == PIPE || trim[k] == RED_I || trim[k] == RED_O)
		{
			ft_new_token(bash, j + k, j + k + 1);
			k++;
		}
		else
			k = ft_gather_trim(bash, trim, j, k);
	}
}

void	ft_do_we_pipe(t_bash *bash)
{
	if (bash->first_token->next)
	{
		if (!ft_check_tokens(bash))
			ft_create_pipe_list(bash);
	}
}

void	ft_tokenize(t_bash *bash)
{
	size_t	i;
	size_t	j;
	char	*trim;
	char	*cpy;

	i = 0;
	if (!ft_analyze_quotes(bash))
		return ;
	ft_quotes_doll(bash);
	while (i < ft_strlen(bash->input) && bash->input != NULL)
	{
		j = i;
		while (bash->input[i] != ' ' && i < ft_strlen(bash->input))
			i = ft_ignore_quotes(bash->input, i);
		cpy = ft_cpy_from_input(bash, i, j);
		trim = ft_strtrim(cpy, " ");
		if (ft_strcmp(trim, ""))
			ft_token_separators(bash, trim, j);
		free(trim);
		free(cpy);
		i++;
	}
	ft_do_we_pipe(bash);
}
