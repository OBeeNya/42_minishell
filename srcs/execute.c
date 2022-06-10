/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:58:23 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/09 18:04:17 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_exec_path(char **paths, char *cmd)
{
	char			*path;
	DIR				*dir;
	struct dirent	*entry;

	while (*paths)
	{
		if (ft_strncmp(*paths, "/mnt", 4))
		{
			dir = opendir(*paths);
			entry = readdir(dir);
			while (entry)
			{
				if (!ft_strcmp(entry->d_name, cmd))
				{
					path = ft_strjoin(*paths, "/");
					closedir(dir);
					return (path);
				}
				entry = readdir(dir);
			}
			closedir(dir);
		}
		paths++;
	}
	return (NULL);
}

int	ft_get_nb_of_files(char **directories, DIR *dir, struct dirent *entry)
{
	int	i;
	int	j;

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
	int	i;
	int	j;

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
	bash->exec = ft_calloc(j + 1, sizeof(char *));
	if (!bash->exec)
		return ;
	ft_copy_exec(bash, paths, dir, entry);
	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths[j]);
	free(paths);
}
