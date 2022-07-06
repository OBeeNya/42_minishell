/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:27:54 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/06 14:28:16 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fd_in_err_no(t_token *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token->next->str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
