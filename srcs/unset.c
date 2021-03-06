/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:56:51 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/22 18:16:54 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset_cpy_envp(t_bash *bash, char **cpy, char *str)
{	
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (bash->envp[i])
	{
		if (ft_strncmp(bash->envp[i], str, ft_strlen(str)))
		{
			cpy[j] = ft_strdup(bash->envp[i]);
			j++;
		}
		free(bash->envp[i]);
		i++;
	}
	free(bash->envp);
	bash->envp = ft_calloc(i, sizeof(char *));
	if (!bash->envp)
		return ;
}

void	ft_unset_envp(t_bash *bash, char *str)
{
	char	**cpy;
	int		i;

	i = 0;
	while (bash->envp[i])
		i++;
	cpy = ft_calloc(i, sizeof(char *));
	if (!cpy)
		return ;
	ft_unset_cpy_envp(bash, cpy, str);
	i = 0;
	while (cpy[i])
	{
		bash->envp[i] = ft_strdup(cpy[i]);
		free(cpy[i]);
		i++;
	}
	free(cpy);
}

void	ft_unset_env(t_bash *bash, char *str)
{
	t_env	*env;
	t_env	*prev;

	env = bash->env;
	while (ft_strcmp(env->key, str))
		env = env->next;
	prev = bash->env;
	while (prev->next != env)
		prev = prev->next;
	free(env->key);
	free(env->string);
	prev->next = env->next;
	free(env);
}

void	ft_unset(t_pipe *pipe, t_bash *bash)
{
	t_token	*token;

	token = pipe->first_token;
	while (token->type != T_CMD)
		token = token->next;
	if (token->next)
		token = token->next;
	if (ft_is_var(bash, token->str))
	{
		ft_unset_envp(bash, token->str);
		ft_unset_env(bash, token->str);
	}
}
