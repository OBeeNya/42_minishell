/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:58:23 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/05 17:03:01 by baubigna         ###   ########.fr       */
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

void	ft_copy_exec(t_bash *bash, t_env *env, DIR *dir, struct dirent *entry)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (env->values[i])
	{
		if (ft_strncmp(env->values[i], "/mnt", 4))
		{
			dir = opendir(env->values[i]);
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

	dir = NULL;
	entry = NULL;
	env = malloc(sizeof(t_env));
	if (!env)
		return ;
	env = bash->env;
	while (ft_strcmp(env->key, "PATH"))
		env = env->next;
	j = ft_get_nb_of_files(env->values, dir, entry);
	bash->exec = malloc(sizeof(char *) * (j + 1));
	if (!bash->exec)
		return ;
	ft_copy_exec(bash, env, dir, entry);
}
