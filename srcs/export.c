/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:24:13 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/11 19:15:41 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_update_env(t_bash *bash, char *key, char *value, int p)
{
	int		i;
	t_env	*env;
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(key, "=");
	i = 0;
	while (ft_strncmp(bash->envp[i], temp, ft_strlen(temp)))
		i++;
	if (!p)
		temp2 = ft_strjoin(temp, value);
	else
		temp2 = ft_strjoin(bash->envp[i], value);
	free(bash->envp[i]);
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

void	ft_create_env(t_bash *bash, char *key, char *value)
{
	int		i;
	char	**cpy;
	char	*temp;

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
	temp = ft_strjoin(key, "=");
	bash->envp[i] = ft_strjoin(temp, value);
	free(temp);
	ft_export_new_env(bash, key, value);
}

void	ft_dispatch_exporting(t_bash *bash, char *str, int i, int p)
{
	char	*key;
	char	*value;

	key = ft_strndup(str, 0, i);
	if (!p)
		value = ft_strndup(str, i + 1, ft_strlen(str) - i - 1);
	else
		value = ft_strndup(str, i + 2, ft_strlen(str) - i - 2);
	if (ft_is_var(bash, key))
		ft_update_env(bash, key, value, p);
	else
		ft_create_env(bash, key, value);
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
		if (!ft_check_export(token->str))
		{
			while (token->str[i] != '=' && i < ft_strlen(token->str)
				&& token->str[i] != '+')
				i++;
			if (token->str[i] == '=')
				ft_dispatch_exporting(bash, token->str, i, 0);
			else if (token->str[i] == '+' && token->str[i + 1] == '=')
				ft_dispatch_exporting(bash, token->str, i, 1);
		}
		else
			ft_wrong_identifier(token->str, bash);
	}
	else
		ft_env(bash, pipe);
}
