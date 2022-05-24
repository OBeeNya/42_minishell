/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:21:56 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/24 15:17:07 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_first_and_last_token(t_token *token)
{
	if (token->previous->type == T_BEG)
	{
		if (token->type == '|')
		{
			ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
			return (0);
		}
		else if (token->type == T_RED_O_SGL || token->type == T_RED_O_DBL
			|| token->type == T_RED_I_SGL || token->type == T_RED_I_DBL)
		{
			ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
			return (0);
		}
	}
	else
	{
		if (token->type == T_RED_I_SGL || token->type == T_RED_I_DBL
			|| token->type == T_RED_O_SGL || token->type == T_RED_I_DBL)
		{
			ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
			return (0);
		}
	}
	return (1);
}

int	ft_check_middle_tokens(t_token *token)
{
	char	*s1;
	char	*s2;

	s1 = NULL;
	s2 = NULL;
	if (ft_is_token_sep(token) && ft_is_token_sep(token->next))
	{
		s1 = ft_strjoin("syntar error near unexpected '", token->next->str);
		s2 = ft_strjoin(s1, "'\n");
		ft_putstr_fd(s2, 2);
		free(s1);
		free(s2);
		return (0);
	}
	else if ((ft_is_token_sep(token) || token->type == T_PIPE)
		&& token->next->type == T_PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		return (0);
	}
	return (1);
}

void	ft_check_tokens(t_bash *bash)
{
	bash->first_token = ft_first_token(bash);
	bash->first_token = bash->first_token->next;
	if (!ft_check_first_and_last_token(bash->first_token))
		return ;
	while (bash->first_token->next)
	{
		if (!ft_check_middle_tokens(bash->first_token))
			return ;
		bash->first_token = bash->first_token->next;
	}
	if (bash->first_token->previous->type != T_BEG)
		if (!ft_check_first_and_last_token(bash->first_token))
			return ;
	bash->first_token = ft_first_token(bash);
}

int	ft_analyze_quotes(t_bash *bash)
{
	if (ft_are_there_quotes(bash) && !ft_check_quotes(bash))
	{
		ft_putstr_fd("quotes not closed\n", 2);
		return (0);
	}
	return (1);
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
	while (i < ft_strlen(bash->input))
	{
		j = i;
		while (bash->input[i] != ' ' && i < ft_strlen(bash->input))
			i = ft_ignore_quotes(bash->input, i);
		cpy = ft_cpy_from_input(bash, i, j);
		trim = ft_strtrim(cpy, " ");
		if (ft_strcmp(trim, ""))
			ft_new_token(bash, j, i);
		free(trim);
		free(cpy);
		i++;
	}
	ft_check_tokens(bash);
}
