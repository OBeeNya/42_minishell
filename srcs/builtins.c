/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 15:47:04 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/25 17:15:33 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char *input)
{
	char	cmd1[6];
	char	cmd2[9];
	int		i;
	char	*echo;

	i = 0;
	if (ft_strlen(input) < 5)
		return ;
	while (i < 5)
	{
		cmd1[i] = input[i];
		i++;
	}
	cmd1[i] = '\0';
	i = 0;
	while (i < 8)
	{
		cmd2[i] = input[i];
		i++;
	}
	cmd2[i] = '\0';
	if (!ft_strcmp(cmd2, "echo -n "))
	{
		echo = malloc(sizeof(char) * ft_strlen(input) - 8);
		if (!echo)
			return ;
		while ((size_t)i < ft_strlen(input))
		{
			echo[i - 8] = input[i];
			i++;
		}
		echo[i] = '\0';
		printf("%s", ft_trim(echo));
		free(echo);
	}
	else if (!ft_strcmp(cmd1, "echo "))
	{
		i = 5;
		echo = malloc(sizeof(char) * ft_strlen(input) - 5);
		if (!echo)
			return ;
		while ((size_t)i < ft_strlen(input))
		{
			echo[i - 5] = input[i];
			i++;
		}
		echo[i] = '\0';
		printf("%s\n", ft_trim(echo));
		free(echo);
	}
}

void	builtins(char *input)
{
	ft_echo(input);
//	cd(input);
//	pwd(input);
//	export(input);
//	unset(input);
//	env(input);
//	exit(input);
}
