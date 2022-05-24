/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:58:23 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/18 15:54:11 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
int	main(int ac, char **av, char **env)
{
	char	*a[] = {"./ls", "-la", NULL};
	int		e = execve("/usr/bin/ls", a, env);
	return (0);
}
*/

int	ft_get_nb_of_files(char **directories, DIR *dir, struct dirent *entry)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (directories[i])
	{
		if (ft_strncmp(directories[i], "/mnt", 4))
		{
			dir = opendir(directories[i]);
			entry = readdir(dir);
			while (entry)
			{
				if (entry->d_name[0] != '.')
					j++;
				entry = readdir(dir);
			}
			closedir(dir);
		}
		i++;
	}
	return (j);
}

void	ft_copy_exec(t_bash *bash, char **paths, DIR *dir, struct dirent *entry)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (paths[i])
	{
		if (ft_strncmp(paths[i], "/mnt", 4))
		{
			dir = opendir(paths[i]);
			entry = readdir(dir);
			while (entry)
			{
				if (entry->d_name[0] != '.')
				{
					bash->exec[j] = ft_strdup(entry->d_name);
					j++;
				}
				entry = readdir(dir);
			}
			closedir(dir);
		}
		i++;
	}
	bash->exec[j] = NULL;
}

void	ft_get_exec(t_bash *bash)
{
	DIR				*dir;
	struct dirent	*entry;
	int				j;
	t_env			*env;
	char			**paths;

	dir = NULL;
	entry = NULL;
	env = bash->env;
	while (ft_strcmp(env->key, "PATH"))
		env = env->next;
	paths = ft_split(env->string, ":");
	j = ft_get_nb_of_files(paths, dir, entry);
	bash->exec = calloc(j + 1, sizeof(char *));
	if (!bash->exec)
		return ;
	ft_copy_exec(bash, paths, dir, entry);
	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths[j]);
	free(paths);
}
