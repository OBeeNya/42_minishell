/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:44:30 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/03 14:23:46 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_all(t_bash *bash)
{
	free(bash->input);
	while (bash->first_token->next)
	{
		bash->first_token = bash->first_token->next;
		free(bash->first_token->previous);
	}
	free(bash->first_token);
}
