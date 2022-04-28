/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:33:55 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/28 14:54:08 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_initialize_bash(t_bash *bash, char **envp)
{
	bash->env = envp;
//	ft_get_exec(bash->env);
	bash->input = NULL;
	bash->first_token = NULL;
}
