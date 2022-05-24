/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:44:30 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/19 18:26:21 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env(t_bash *bash)
{
	t_env	*temp;
	t_env	*next;

	if (bash->env)
	{
		temp = bash->env;
		next = temp->next;
		free(temp->key);
		free(temp);
		temp = next;
		while (temp)
		{
			next = temp->next;
			free(temp->key);
			free(temp->string);
			free(temp);
			temp = next;
		}
		bash->env = NULL;
		free(bash->env);
	}
}

void	ft_free_tokens(t_bash *bash)
{
	t_token	*temp;
	t_token	*next;

	if (bash->first_token)
	{
		temp = bash->first_token;
		while (temp)
		{
			next = temp->next;
			free(temp->str);
			free(temp);
			temp = next;
		}
		bash->first_token = NULL;
		free(bash->first_token);
	}
}

void	ft_free_all(t_bash *bash)
{
	int	i;

	i = 0;
	while (bash->exec[i])
	{
		free(bash->exec[i]);
		i++;
	}
	free(bash->exec);
	free(bash->input);
	ft_free_env(bash);
	ft_free_tokens(bash);
}
