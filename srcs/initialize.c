/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:33:55 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/05 17:07:01 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_new_env(t_bash *bash, char *key, char **values)
{
	t_env	*last;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	last = bash->env;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
	new->key = key;
	new->values = values;
}

void	ft_create_first_env(t_bash *bash)
{
	bash->env = malloc(sizeof(t_env));
	if (!bash->env)
		return ;
	bash->env->key = ft_strdup(" === BEG OF ENV === ");
	bash->env->values = NULL;
	bash->env->next = NULL;
}

void	ft_get_env(t_bash *bash, char **envp)
{
	int		i;
	char	*key;
	char	**temp;
	char	**values;

	i = 0;
	temp = NULL;
	values = NULL;
	ft_create_first_env(bash);
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		key = temp[0];
		values = ft_split(temp[1], ':');
		ft_new_env(bash, key, values);
		i++;
	}
	free(temp);
	free(key);
	free(values);
}

void	ft_initialize_bash(t_bash *bash, char **envp)
{
	bash->input = NULL;
	bash->env = NULL;
	bash->exec = NULL;
	ft_create_first_token(bash);
	ft_get_env(bash, envp);
	ft_get_exec(bash);
}
