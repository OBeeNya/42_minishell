/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:38:15 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/18 14:02:31 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_bash	g_bash;

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

int	ft_is_there_dolls(char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (line && *line)
	{
		while (line[k + 1])
		{
			if (line[k] == '$')
				i++;
			k++;
		}
	}
	if (!i)
		return (0);
	else
		return (1);
}

void	ft_eof_heredoc(char *unquoted)
{
	ft_putstr_fd("> minishell: warning: here-document at line delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(unquoted, 2);
	ft_putstr_fd("')\n", 2);
	exit(0);
}

void	ft_fork_heredoc(char *filename, int quotes, char *unquoted, int fd)
{
	char	*line;
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		signal(SIGINT, heredoc_handler);
		while (1)
		{
			line = readline("> ");
			if (!line)
				ft_eof_heredoc(unquoted);
			line = ft_expand_heredoc(line, &g_bash, quotes);
			if (!ft_strcmp(line, unquoted))
				break ;
			write(fd, line, ft_strlen(line) * sizeof(char));
			write(fd, "\n", 1);
			free(line);
		}
		free(unquoted);
		free(filename);
		ft_free_all(&g_bash, true);
	}
	if (0 < waitpid(pid, &g_bash.err, 0) && WIFEXITED(g_bash.err))
		g_bash.err = WEXITSTATUS(g_bash.err);
	ft_handle_signals();
}

void	ft_heredoc(t_pipe *pipe, char *delim)
{
	char	*filename;
	char	*unquoted;
	int		fd;
	int		quotes;

	filename = ft_strdup("h");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	quotes = ft_are_there_quotes(delim);
	unquoted = ft_unquote_delim(delim);
	signal(SIGINT, SIG_IGN);
	ft_fork_heredoc(filename, quotes, unquoted, fd);
	if (pipe->fdin)
		close(pipe->fdin);
	pipe->fdin = open(filename, O_RDONLY);
	if (pipe->fdin == -1)
		return ;
	free(filename);
	free(unquoted);
	close(fd);
	unlink("h");
}
