/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:24:13 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/06 14:44:33 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_update_env(t_bash *bash, char *key, char *value)
{
	int		i;
	t_env	*env;
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(key, "=");
	i = 0;
	while (ft_strncmp(bash->envp[i], temp, ft_strlen(temp)))
		i++;
	free(bash->envp[i]);
	temp2 = ft_strjoin(temp, value);
	bash->envp[i] = ft_strdup(temp2);
	free(temp);
	free(temp2);
	env = bash->env;
	while (ft_strcmp(env->key, key))
		env = env->next;
	free(env->string);
	env->string = ft_strdup(value);
}

void	ft_export_new_env(t_bash *bash, char *key, char *value)
{
	t_env	*last;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return ;
	last = bash->env;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
	new->key = ft_strdup(key);
	new->string = ft_strdup(value);
}

void	ft_create_env(t_bash *bash, char *str, char *key, char *value)
{
	int		i;
	char	**cpy;

	i = 0;
	while (bash->envp[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	if (!cpy)
		return ;
	ft_cpy_envp(bash, cpy);
	i = 0;
	while (cpy[i])
	{
		bash->envp[i] = ft_strdup(cpy[i]);
		free(cpy[i]);
		i++;
	}
	free(cpy);
	bash->envp[i] = ft_strdup(str);
	ft_export_new_env(bash, key, value);
}

void	ft_dispatch_exporting(t_bash *bash, char *str, int i)
{
	char	*key;
	char	*value;

	key = ft_strndup(str, 0, i);
	value = ft_strndup(str, i + 1, ft_strlen(str) - i - 1);
	if (ft_is_var(bash, key))
		ft_update_env(bash, key, value);
	else
		ft_create_env(bash, str, key, value);
	free(key);
	free(value);
}

void	ft_export(t_pipe *pipe, t_bash *bash)
{
	t_token	*token;
	size_t	i;

	token = pipe->first_token;
	while (token->type != T_CMD)
		token = token->next;
	if (token->next && token->next->type == T_STR)
	{
		token = token->next;
		i = 0;
		if (token->str[i] == '_' || ft_isalpha(token->str[i]))
		{
			while (token->str[i] != '=' && i < ft_strlen(token->str))
				i++;
			if (token->str[i] == '=')
				ft_dispatch_exporting(bash, token->str, i);
		}
		else
			ft_wrong_identifier(token->str, bash);
	}
	else
		ft_env(bash);
}
