/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baubigna <baubigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:27:02 by baubigna          #+#    #+#             */
/*   Updated: 2022/06/09 18:04:31 by baubigna         ###   ########.fr       */
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
	T_CMD,
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
	char			*string;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	char			*cmd;
	char			**args;
	t_token			*first_token;
	int				fdin;
	int				fdout;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_bash
{
	char	**exec;
	char	**envp;
	char	*input;
	t_env	*env;
	t_token	*first_token;
	t_pipe	*pipes;
}	t_bash;

/*---------------------------------------------------------------------------*/

/* args.c */
int		ft_count_args(t_token *token);
void	ft_cpy_args(t_pipe *pipe);
void	ft_get_args(t_bash *bash);

/* builtins.c */
int		ft_is_builtin(char *cmd);
void	ft_dispatch_builtins(t_pipe *pipe);

/* cd.c */
void	ft_cd(t_pipe *pipe);

/* cleaning.c */
void	ft_free_bash_env(t_bash *bash);
void	ft_free_env(t_bash *bash);
void	ft_free_tokens(t_token *token);
void	ft_free_pipes(t_bash *bash);
void	ft_free_all(t_bash *bash);

/* commands.c */
void	ft_assign_cmd(t_pipe *next, t_token *lst, int *chev, int *cmd);
int		ft_check_cmd(t_bash *bash);
void	ft_cmd_err(t_pipe *list);
int		ft_is_it_exec(t_bash *bash, t_pipe *list);
int		ft_check_cmd_exec(t_bash *bash);

/* dollars_utils.c */
int		ft_which_doll_case(char *str, size_t *i, int qt);
char	*ft_manage_doll(char *str, size_t *i, t_bash *bash, int qt);
char	*ft_manage_doll_2(char *str, size_t *i, t_bash *bash);
char	*ft_is_var(t_bash *bash, char *str);
void	ft_quotes_doll(t_bash *bash);

/* echo.c */
void	ft_echo(t_pipe *pipe);

/* execute.c */
char	*ft_get_exec_path(char **paths, char *cmd);
int		ft_get_nb_of_files(char **directories, DIR *dir, struct dirent *entry);
void	ft_copy_exec(t_bash *bash, char **paths, DIR *dir, \
	struct dirent *entry);
void	ft_get_exec(t_bash *bash);

/* fork.c */
char	*ft_get_path_str(char *cmd, t_bash *bash);
char	**ft_join_args(t_pipe *pipe);
void	ft_execute_cmd(t_pipe *pipe, t_bash *bash);
void	ft_forking(t_bash *bash);

/* initialize.c */
void	ft_new_env(t_bash *bash, char *key, char *string);
void	ft_create_first_env(t_bash *bash);
void	ft_get_env(t_bash *bash, char **envp);
void	ft_cpy_env(t_bash *bash, char **envp);
void	ft_initialize_bash(t_bash *bash, char **envp);

/* parse_utils.c */
int		ft_is_token_sep(t_token *token);
char	*ft_cpy_from_input(t_bash *bash, size_t i, size_t j);
int		ft_is_just_spaces(char *input);
void	ft_trim_quotes(t_token *new);
void	ft_free_split(char **split);

/* pipe_creation.c */
void	ft_create_first_pipe(t_bash *bash);
void	ft_add_back_token(t_pipe *pipe, t_token *token);
void	ft_create_new_pipe(t_bash *bash, t_token *token);
int		ft_count_pipes(t_token *first);
void	ft_create_pipe_list(t_bash *bash);

/* print.c */
void	ft_print_tokens(t_bash *bash);
void	ft_print_env(t_bash *bash, char *key);
void	ft_print_pipes(t_bash *bash);
void	ft_print_envp(t_bash *bash);

/* quotes_dollars.c */
char	*ft_double(char *str, size_t *i, t_bash *bash, char *final_str);
char	*ft_single(char *str, size_t *i, char *final_str);
char	*ft_dollars(char *str, size_t *i, t_bash *bash, char *final_str);
char	*ft_else(char *str, size_t *i, char *final_str);
char	*ft_is_quotes(char *str, t_bash *bash);

/* quotes_utils.c */
char	*ft_dbl_quotes(char *str, size_t *i, t_bash *bash, char *final_str);
char	*ft_sgl_quotes(char *str, size_t *i, char *final_str);
int		ft_count(char *str, int i);
int		ft_count_quotes(char *str);
size_t	ft_index_closing_quote(char *str, size_t i);

/* quotes.c */
int		ft_check_quotes(t_bash *bash);
int		ft_are_there_quotes(t_bash *bash);
size_t	ft_ignore_quotes(char *str, size_t i);
int		ft_analyze_quotes(t_bash *bash);

/* signals.c */
void	ctrl_handler(int signum);

/* token_check.c */
int		ft_check_first_and_last_token(t_token *token);
int		ft_check_middle_tokens(t_token *token);
int		ft_check_tokens(t_bash *bash);
void	ft_do_we_pipe(t_bash *bash);

/* token_creation.c */
void	ft_create_first_token(t_bash *bash);
t_token	*ft_first_token(t_token *token);
t_token	*ft_last_token(t_token *token);
void	ft_get_token_type(t_token *new);
void	ft_new_token(t_bash *bash, size_t j, size_t i);

/* tokenize.c */
size_t	ft_gather_trim(t_bash *bash, char *trim, size_t j, size_t k);
void	ft_token_separators(t_bash *bash, char *trim, size_t j);
void	ft_tokenize(t_bash *bash);

#endif
