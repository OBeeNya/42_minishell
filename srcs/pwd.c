/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamin <benjamin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:04:31 by benjamin          #+#    #+#             */
/*   Updated: 2022/06/15 13:10:23 by benjamin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(void)
{
	char	buf[MAX_LINE_LEN];
	char	*cwd;

	cwd = getcwd(buf, MAX_LINE_LEN);
	cwd = ft_strjoin(cwd, "\n");
	ft_putstr_fd(cwd, 2);
	free(cwd);
}
