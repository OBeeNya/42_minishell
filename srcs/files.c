/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:32:12 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/28 13:43:33 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_file(char *filepath)
{
	struct stat	buf;
	int			a;

	a = stat(filepath, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFREG)
		return (a + 1);
	else
		return (0);
}
