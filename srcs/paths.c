/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:44:12 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/28 13:31:34 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_get_paths(char **envp)
{
	int		i;
	char	**path_env;
	char	**all_paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			path_env = ft_split(envp[i], '=');
			all_paths = ft_split(path_env[1], ':');
			break ;
		}
		i++;
	}
	free(path_env);
	return (all_paths);
}
