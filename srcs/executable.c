/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:44:38 by hcherpre          #+#    #+#             */
/*   Updated: 2022/07/06 15:16:28 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_executable(t_bash *bash)
{
	char	*cwd;
	t_pipe	*pass;

	pass = bash->pipes->next;
	if (pass->cmd[0] == '.')
		cwd = ft_executable_2(pass->cmd);
	else if (pass->cmd[0] == '/')
		cwd = ft_strdup(pass->cmd);
	else
		return ;
	ft_execve(cwd, bash, pass->cmd);
	free (cwd);
}

char	*ft_executable_2(char *cmd)
{
	int		i;
	char	*cwd;
	char	*temp;
	char	*new;
	char	buf[MAX_LINE_LEN];

	i = 0;
	cwd = getcwd(buf, MAX_LINE_LEN);
	while (cmd[i] != '/')
		i++;
	new = ft_strndup(cmd, i, ft_strlen(cmd) - 1);
	if (i == 2)
	{
		temp = ft_delete_dir(cwd);
		cwd = ft_strjoin(temp, new);
		free (temp);
	}
	else
		cwd = ft_strjoin(cwd, new);
	free(new);
	return (cwd);
}

void	ft_execve(char *cwd, t_bash *bash, char *cmd)
{
	int		k;
	pid_t	pid;
	char	*args[2];

	args[0] = "";
	args[1] = NULL;
	k = access(cwd, F_OK);
	if (!k)
	{
		pid = fork();
		if (pid == -1)
			return ;
		else if (!pid)
			execve(cwd, args, bash->envp);
		else
			wait(0);
	}
	else
	{
		// if (cmd[0] == '/' || cmd == '.')
		// 	ft_err_no_exec(cwd, cmd, bash);
		if (cmd[0] == '/')
			printf("%s: No such file or directory\n", cwd);
		else if (cmd[0] == '.')
			printf("%s: No such file or directory\n", cmd);
	}
}

char	*ft_delete_dir(char *cwd)
{
	int		i;
	int		j;
	char	*new_cwd;

	i = 0;
	i = ft_strlen(cwd);
	while (cwd[i] != '/')
		i--;
	i--;
	new_cwd = ft_calloc(ft_strlen(cwd) - ft_strlen(cwd) + i + 2, sizeof(char));
	if (!new_cwd)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		new_cwd[j] = cwd[j];
		j++;
	}
	return (new_cwd);
}
