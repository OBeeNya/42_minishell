/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:03:14 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/11 19:13:04 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

void	ft_dispatch_builtins(t_pipe *pipe, t_bash *bash)
{
	char	buf[MAX_LINE_LEN];
	char	*old;

	old = getcwd(buf, MAX_LINE_LEN);
	if (!ft_strcmp(pipe->cmd, "echo"))
		ft_echo(pipe);
	if (!ft_strcmp(pipe->cmd, "cd"))
		ft_cd(pipe, bash, old, buf);
	if (!ft_strcmp(pipe->cmd, "pwd"))
		ft_pwd();
	if (!ft_strcmp(pipe->cmd, "export"))
		ft_export(pipe, bash);
	if (!ft_strcmp(pipe->cmd, "unset"))
		ft_unset(pipe, bash);
	if (!ft_strcmp(pipe->cmd, "env"))
		ft_env(bash, pipe);
	if (!ft_strcmp(pipe->cmd, "exit"))
		ft_exit(pipe);
}
