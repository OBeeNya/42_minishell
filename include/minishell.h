/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:27:02 by baubigna          #+#    #+#             */
/*   Updated: 2022/04/28 14:48:40 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "../libft/libft.h"

# define MAX_LINE_LEN 4096
# define SGL_QT 39
# define DBL_QT 34

typedef enum token_types
{
	PIPE = '|',
	RED_I_SGL = '>',
	RED_I_DBL,
	RED_O_SGL = '<',
	RED_O_DBL,
	CMD,
	BUILTIN,
	ENV_VAR,
	STR,
	STR_SGL_QT,
	STR_DBL_QT0
}	t_token_types;

typedef struct s_token
{
	char			*str;
	int				token_type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_bash
{
	char	**env;
	char	**exec;
	char	*input;
	t_token	*first_token;
}	t_bash;

/* builtins.c */
void	builtins(char *input);

/* files.c */
int		ft_check_file(char *filepath);

/* initialize.c */
void	ft_initialize_bash(t_bash *bash, char **envp);

/* parse_utils.c */
char	*ft_trim(char *s);

/* paths.c */
char	**ft_get_paths(char **envp);

/* signals.c */
void	ctrl_handler(int signum);

/* tokenize.c */
int		ft_check_quotes(t_bash *bash);
int		ft_tokenize(t_bash *bash);

#endif
