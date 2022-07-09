/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:05:04 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/09 18:38:56 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_path_str(char *cmd, t_bash *bash)
{
	char	**paths;
	t_env	*env;
	char	*path;
	int		i;

	if (cmd[0] == '/')
		return (ft_strdup(""));
	env = bash->env;
	path = NULL;
	while (ft_strcmp("PATH", env->key) && env->next)
		env = env->next;
	if (!ft_strcmp(env->key, "PATH"))
	{
		paths = ft_split(env->string, ":");
		path = ft_get_exec_path(paths, cmd);
		i = 0;
		while (paths[i])
			free(paths[i++]);
		free(paths[i]);
		free(paths);
	}
	return (path);
}

char	**ft_join_args(t_pipe *pipe)
{
	char	**arg;
	int		i;

	i = 0;
	arg = NULL;
	if (pipe->args)
	{
		while (pipe->args[i])
			i++;
	}
	arg = ft_calloc(i + 2, sizeof(char *));
	if (!arg)
		return (NULL);
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
	if (args)
	{
		path = ft_get_path_str(pipe->cmd, bash);
		if (path)
		{
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
	}
}

void	ft_execute_no_pipe(t_bash *bash, t_pipe *pass)
{
	pid_t	pid;

	ft_dup_fds(pass);
	if (pass->cmd)
	{
		if (ft_is_builtin(pass->cmd))
			ft_dispatch_builtins(pass, bash);
		else
		{
			pid = fork();
			if (pid == -1)
				return ;
			else if (!pid)
				ft_execute_cmd(pass, bash);
			if (0 < waitpid(pid, &bash->err, 0) && WIFEXITED(bash->err))
				bash->err = WEXITSTATUS(bash->err);
		}
	}
	ft_close_fds(pass);
}

void	ft_forking(t_bash *bash)
{
	t_pipe	*pass;
	int		i;
	int		k;

	k = 0;
	pass = bash->pipes->next;
	i = nb_pipes(pass);
	if (!pass->next)
		ft_execute_no_pipe(bash, pass);
	else
		ft_pipe(bash, i, pass, k);
}
