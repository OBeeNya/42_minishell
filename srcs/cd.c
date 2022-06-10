/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:02:47 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/09 18:15:03 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd_here(t_token *token, char buf[MAX_LINE_LEN], int c)
{
	char	*temp;
	char	*temp2;

	temp = ft_calloc(ft_strlen(token->str), sizeof(char));
	if (!temp)
		return ;
	c = 0;
	while (token->str[c + 1])
	{
		temp[c] = token->str[c + 1];
		c++;
	}
	temp2 = ft_strjoin(getcwd(buf, MAX_LINE_LEN), temp);
	free(temp);
	c = chdir(temp2);
	free(temp2);
	if (c)
	{
		temp = ft_strjoin("cd: ", token->str);
		temp2 = ft_strjoin(temp, ": Not a directory\n");
		free(temp);
		ft_putstr_fd(temp2, 2);
		free(temp2);
	}
	(void) c;
}

void	ft_cd(t_pipe *pipe)
{
	t_token	*token;
	char	*temp;
	char	*temp2;
	char	buf[MAX_LINE_LEN];
	int		c;

	token = pipe->first_token;
	while (token->type != T_CMD)
		token = token->next;
	if (!token->next || token->next->type != T_STR)
	{
		ft_putstr_fd("this command only takes relative or absolute paths\n", 2);
		return ;
	}
	token = token->next;
	c = 0;
	if (!ft_strncmp(token->str, "./", 2))
		ft_cd_here(token, buf, c);
	// {
	// 	temp = ft_calloc(ft_strlen(token->str), sizeof(char));
	// 	if (!temp)
	// 		return ;
	// 	c = 0;
	// 	while (token->str[c + 1])
	// 	{
	// 		temp[c] = token->str[c + 1];
	// 		c++;
	// 	}
	// 	temp2 = ft_strjoin(getcwd(buf, MAX_LINE_LEN), temp);
	// 	free(temp);
	// 	c = chdir(temp2);
	// 	free(temp2);
	// 	if (c)
	// 	{
	// 		temp = ft_strjoin("cd: ", token->str);
	// 		temp2 = ft_strjoin(temp, ": Not a directory\n");
	// 		free(temp);
	// 		ft_putstr_fd(temp2, 2);
	// 		free(temp2);
	// 	}
	// 	(void) c;
	// }
	else if (!ft_strncmp(token->str, "..", 2))
	{
		temp = getcwd(buf, MAX_LINE_LEN);
	}
	else if (token->str[0] == '/')
	{
		c = chdir(token->str);
		if (c)
		{
			temp = ft_strjoin("cd: ", token->str);
			temp2 = ft_strjoin(temp, ": Not a directory\n");
			free(temp);
			ft_putstr_fd(temp2, 2);
			free(temp2);
		}
		(void) c;
	}
	else
	{
		temp2 = ft_strjoin(getcwd(buf, MAX_LINE_LEN), "/");
		temp = ft_strjoin(temp2, token->str);
		free(temp2);
		c = chdir(temp);
		free(temp);
		if (c)
		{
			temp = ft_strjoin("cd: ", token->str);
			temp2 = ft_strjoin(temp, ": Not a directory\n");
			free(temp);
			ft_putstr_fd(temp2, 2);
			free(temp2);
		}
		(void) c;
	}
}
