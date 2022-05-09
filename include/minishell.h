/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:27:02 by baubigna          #+#    #+#             */
/*   Updated: 2022/05/05 17:02:44 by baubigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
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
# define RED_I 60
# define RED_O 62
# define PIPE 124

typedef enum token_types
{
	T_RED_I_SGL = '<',
	T_RED_O_SGL = '>',
	T_RED_O_DBL,
	T_RED_I_DBL,
	T_STR,
	T_BEG,
	T_PIPE = '|'
}	t_token_types;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			**values;
	struct s_env	*next;
}	t_env;

typedef struct s_bash
{
	char	**exec;
	char	*input;
	char	**paths;
	t_env	*env;
	t_token	*first_token;
}	t_bash;

/* builtins.c */
void	ft_echo(char *input);
void	builtins(char *input);

/* cleaning.c */
void	ft_free_all(t_bash *bash);

/* execute.c */
int		ft_get_nb_of_files(char **directories, DIR *dir, struct dirent *entry);
void	ft_copy_exec(t_bash *bash, t_env *env, DIR *dir, struct dirent *entry);
void	ft_get_exec(t_bash *bash);

/* files.c */
int		ft_check_file(char *filepath);

/* initialize.c */
void	ft_new_env(t_bash *bash, char *key, char **values);
void	ft_create_first_env(t_bash *bash);
void	ft_get_env(t_bash *bash, char **envp);
void	ft_initialize_bash(t_bash *bash, char **envp);

/* parse_utils.c */
int		ft_is_token_sep(t_token *token);
char	*ft_cpy_from_input(t_bash *bash, size_t i, size_t j);

/* quotes.c */
int		ft_check_quotes(t_bash *bash);
int		ft_are_there_quotes(t_bash *bash);
size_t	ft_ignore_quotes(t_bash *bash, size_t i);

/* signals.c */
void	ctrl_handler(int signum);

/* token_creation.c */
void	ft_create_first_token(t_bash *bash);
t_token	*ft_first_token(t_bash *bash);
void	ft_print_tokens(t_bash *bash);
t_token	*ft_last_token(t_bash *bash);
void	ft_new_token(t_bash *bash, size_t j, size_t i);

/* tokenize.c */
int		ft_check_first_and_last_token(t_token *token);
int		ft_middle_tokens(t_bash *bash);
void	ft_check_tokens(t_bash *bash);
int		ft_tokenize(t_bash *bash);

#endif
