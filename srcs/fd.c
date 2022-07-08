/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:29:58 by baubigna          #+#    #+#             */
/*   Updated: 2022/07/08 13:48:23 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup_fds(t_pipe *pipe)
{
	pipe->fdin_init = dup(0);
	pipe->fdout_init = dup(1);
	dup2(pipe->fdin, 0);
	dup2(pipe->fdout, 1);
}

void	ft_close_fds(t_pipe *pipe)
{
	dup2(pipe->fdin_init, 0);
	dup2(pipe->fdout_init, 1);
	close(pipe->fdin_init);
	close(pipe->fdout_init);
	if (pipe->fdin != 0 && pipe->fdin != -1)
		close(pipe->fdin);
	if (pipe->fdout != 1 && pipe->fdout != -1)
		close(pipe->fdout);
}

void	ft_update_fdout(t_pipe *pipe, t_token *token)
{
	if (token->type == T_RED_O_SGL)
	{
		if (pipe->fdout != 1)
			close(pipe->fdout);
		pipe->fdout = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC,
				00644);
	}
	else if (token->type == T_RED_O_DBL)
	{
		if (pipe->fdout != 1)
			close(pipe->fdout);
		pipe->fdout = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND,
				00644);
	}
}

int	ft_update_fd_in_out(t_pipe *pipe, t_bash *bash)
{
	t_token	*token;

	token = pipe->first_token;
	while (token)
	{
		if (token->type == T_RED_I_SGL)
		{
			if (pipe->fdin != 0)
				close(pipe->fdin);
			pipe->fdin = open(token->next->str, O_RDONLY, 00644);
			if (pipe->fdin == -1)
			{
				ft_fd_in_err_no(token, bash);
				return (1);
			}
		}
		else if (token->type == T_RED_I_DBL)
			ft_heredoc(pipe, token->next->str, bash);
		else if (token->type == T_RED_O_SGL || token->type == T_RED_O_DBL)
			ft_update_fdout(pipe, token);
		if (ft_err_echo_dir(pipe, bash))
			return (1);
		token = token->next;
	}
	return (0);
}

int	ft_update_fds(t_bash *bash)
{
	t_pipe	*pipe;

	pipe = bash->pipes->next;
	while (pipe)
	{
		if (ft_update_fd_in_out(pipe, bash))
			return (1);
		pipe = pipe->next;
	}
	return (0);
}
