/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:05:04 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/09 17:14:12 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_path_str(char *cmd, t_bash *bash)
{
	char	**paths;
	t_env	*env;
	char	*path;
	int		i;

	env = bash->env;
	while (ft_strcmp("PATH", env->key))
		env = env->next;
	paths = ft_split(env->string, ":");
	path = ft_get_exec_path(paths, cmd);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths[i]);
	free(paths);
	return (path);
}

char	**ft_join_args(t_pipe *pipe)
{
	char	**arg;
	int		i;

	i = 0;
	if (pipe->args)
	{
		while (pipe->args[i])
			i++;
	}
	arg = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	arg[i] = ft_strjoin("./", pipe->cmd);
	i++;
	if (pipe->args)
	{
		while (pipe->args[i - 1])
		{
			arg[i] = ft_strdup(pipe->args[i - 1]);
			i++;
		}
	}
	return (arg);
}

void	ft_execute_cmd(t_pipe *pipe, t_bash *bash)
{
	char	**args;
	char	*path;
	char	*cmd;
	int		e;

	args = ft_join_args(pipe);
	path = ft_get_path_str(pipe->cmd, bash);
	cmd = ft_strjoin(path, pipe->cmd);
	e = execve(cmd, args, bash->envp);
	e = 0;
	while (args[e])
		free(args[e++]);
	free(args[e]);
	free(args);
	free(path);
	free(cmd);
}

void	ft_forking(t_bash *bash)
{
	t_pipe	*pass;
	pid_t	pid;

	pass = bash->pipes->next;
	while (pass)
	{
		if (ft_is_builtin(pass->cmd))
			ft_dispatch_builtins(pass);
		else
		{
			pid = fork();
			if (pid == -1)
				return ;
			else if (!pid)
				ft_execute_cmd(pass, bash);
		}
		pass = pass->next;
	}
}
