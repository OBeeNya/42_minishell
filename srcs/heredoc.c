/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:38:15 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/05 17:03:36 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_unquote_delim(char *delim)
{
	char	*unquoted;
	size_t	l;

	l = ft_strlen(delim) - ft_count_quotes(delim) + 1;
	unquoted = ft_calloc(l, sizeof(char));
	if (!unquoted)
		return (NULL);
	ft_unquoting(unquoted, delim);
	return (unquoted);
}

char	*ft_expand_heredoc(char *line)
{
	(void) line;
	return (NULL);
}

void	ft_heredoc(t_pipe *pipe, char *delim)
{
	char	*line;
	char	*filename;
	char	*unquoted;
	// pid_t	pid;
	int		fd;

	// pid = fork();
	// if (pid == -1)
	// 	return ;
	// else if (!pid)
	// {
		filename = ft_strdup("h");
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		unquoted = ft_unquote_delim(delim);
		while (1)
		{
			line = readline("> ");
			// if (!ft_are_there_quotes(line))
			// 	line = ft_expand_heredoc(line);
			if (!ft_strcmp(line, unquoted))
				break ;
			write(fd, line, ft_strlen(line) * sizeof(char));
			write(fd, "\n", 1);
		}
		if (pipe->fdin)
			close(pipe->fdin);
		pipe->fdin = open(filename, O_RDONLY);
		if (pipe->fdin == -1)
			return ;
		free(filename);
		free(unquoted);
	// }
	// else
	// 	wait(0);
}
