/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:21:56 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/05 18:26:15 by baubigna         ###   ########.fr       */
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
	if (ft_is_token_sep(token) && ft_is_token_sep(token->next))
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin("syntar error near unexpected '", \
			token->next->str), "'\n"), 2);
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

/*
size_t	ft_tokenize_redirections(t_bash *bash, size_t i)
{
	if (bash->input[i] == PIPE)
	{
		ft_new_token(bash, i, i + 1, T_PIPE);
		return (i + 1);
	}
	else if (bash->input[i] == RED_I && bash->input[i + 1] == RED_I)
	{
		ft_new_token(bash, i, i + 2, T_RED_I_DBL);
		return (i + 2);
	}
	else if (bash->input[i] == RED_I)
	{
		ft_new_token(bash, i, i + 1, T_RED_I_SGL);
		return (i + 1);
	}
	else if (bash->input[i] == RED_O && bash->input[i + 1] == RED_O)
	{
		ft_new_token(bash, i, i + 2, T_RED_O_DBL);
		return (i + 2);
	}
	else if (bash->input[i] == RED_O)
		ft_new_token(bash, i, i + 1, T_RED_O_SGL);
	return (i + 1);
}
*/

int	ft_tokenize(t_bash *bash)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_are_there_quotes(bash))
	{
		if (!ft_check_quotes(bash))
		{
			ft_putstr_fd("quotes not closed\n", 2);
			return (0);
		}
	}
	while (i < ft_strlen(bash->input))
	{
		j = i;
		while (bash->input[i] != ' ' && i < ft_strlen(bash->input))
			i = ft_ignore_quotes(bash, i);
		if (ft_strcmp(ft_strtrim(ft_cpy_from_input(bash, i, j), " "), ""))
			ft_new_token(bash, j, i);
		i++;
	}
	ft_check_tokens(bash);
	return (1);
}

/*
void	ft_transform_args(t_token *first_token)
{
	t_token	*cursor;

	cursor = first_token;
	while (cursor)
	{
		while(*cursor->str)
		{
			if (*cursor->str == '$')
			{
				
			}
			*cursor->str++;
		}
		cursor = cursor.next;
	}
}
*/
