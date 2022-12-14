/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:27:55 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/04 10:32:06 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdio.h>
# include	<string.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<fcntl.h>
# include	<sys/ioctl.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../libft/libft.h"

# define PIPE 			1
# define WORD 			2
# define NONE 			3
# define ESPACE 		4
# define REDIR_GREATER	5
# define REDIR_LESSER	6
# define DOUBLE_GREATER	7
# define DOUBLE_LESSER	8
# define ENEWLINE		9
# define PROMPT			"\e[1;32m➜  \e[1;31mMini👽shell\e[1;33m ➤ \e[1;37m\e[m"

typedef struct s_free{
	void			*to_free;
	struct s_free	*next;
}	t_free;

typedef struct s_global{
	int		exist_status;
	int		catch_signal;
	int		quotes_count;
	char	*tmp_readline;
	int		shel_level;
	int		skip;
	t_free	*free_collect;
}	t_global;

t_global	g_global;

typedef struct s_lexer{
	int		i;
	char	*token;
}	t_lexer;

typedef struct s_env{
	char			*value;
	char			*name;
	struct s_env	*next;
}	t_env;

typedef struct s_tokens_list{
	int						type;
	char					*value;
	struct s_tokens_list	*next;
}	t_tokens_list;

typedef struct s_redirection {
	char					*f_name;
	int						type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command{
	char				**command;
	bool				is_delimter_in_quotes;
	pid_t				pid;
	t_redirection		*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_parse{
	t_tokens_list	*current_token;
	t_command		*cmd;
	t_redirection	*redirections;
	char			**cmd_arg;
	int				size;
}	t_parse;

typedef struct s_main{
	t_tokens_list	*list;
	t_command		*cmd;
	t_env			*h_env;
	char			*line;
	bool			dollar_type;

}	t_main;

/********************collecter*****************/

t_free			*ft_lstnew1(void *content);
t_free			*ft_lstlast1(t_free *lst);
void			ft_lstadd_back1(t_free **collecter, t_free *new);
void			*ft_malloc(size_t size);
void			collect_libft_readline(void *to_collect);
void			free_list(t_free *list);

/****************libft Function****************/

char			**ft_split1(char *env);
char			*ft_strdup1(char *str);
int				get_lenght(char *ln, char c);
char			*ft_strchr1(char *str, char c);
int				ft_strcmp(char *str, char *ptr);
int				lenght_of_word(char *ln, int *index);
char			*ft_strjoin1(char *s1, char *s2);
void			*ft_malloc(size_t size);

/*****************env Function*****************/

void			ft_initialize_env(t_main *var, int ac, char **av, char **env);
t_env			*create_env_list(t_env *p_env, char **env);
void			add_env_node(t_env *p_env, char *Name, char *Value);
t_env			*create_first_node(char *Name, char *Value);
char			*get_s1(char *env, char **str, int i);

/****************lexer Function****************/

t_tokens_list	*ft_lexer(char *line, t_main *v_main);
void			get_symbol(t_tokens_list *var, char *ln,
					int *index, t_main *v_main);
void			add_token_node(t_tokens_list *var, int type, char *value);
char			*treat_quotes(int *index, char *ln, t_main *v_main);
int				expand_dollar(char **token, t_main *v_main);
int				search_for_dollar(char *token);
int				dollar_name_len(char **token);
void			get_after_dollar(char **token, int	*index, char **d_name);
void			get_inside_bracket(char **token, int *index, char **d_name);
int				edit_token(char **token, t_main *v_main);
int				join_word(t_tokens_list *v_main);
char			*take_word(char *ln, int *index);
int				alpha_numeric(char c);
void			check_dollar_even(char **token, int *index, t_main *v_main);
char			*get_dollar_name(char **token, t_main *v_main);
char			*quotes_after_quotes(char *ln, int *index, char type);
int				find_even_quotes(char *ln, int *index, char type);
void			get_delimitter(t_tokens_list *var, char *ln,
					int *index, t_main *v_main);
int				len_inside_quotes1(int i, char *ln, char type);
int				get_token_space(t_tokens_list *var, char *ln, int i);
int				find_even_quotes(char *ln, int *index, char type);
int				check_quotess(char *str);
char			*take_last_part_here(char **token, int *i);
int				delete_space_token(t_tokens_list *head);

/****************syntax Function***************/

int				check_syntax(t_tokens_list *var, t_main *v_main);
void			display_message(char *value);

/****************parse Function****************/

t_command		*ft_parse(t_tokens_list *tokens_list, t_env *h_env);
void			initialize_var(t_parse *var, t_tokens_list *tokens_list);
int				arg_size(char **cmd_arg);
int				ft_strcmp_int(int x, int y);
void			get_cmd_arg(t_parse *var);
char			*traite_herdoc(char *del, t_main *v_main);

/****************builtins functions****************/

int				built_cd(char *path, t_env **our_env);
int				option_n_enbaled(char **cmd_args);
int				built_echo(char **cmd_args);
void			built_env(t_env **our_env);
int				validity_of_var_name(char *var_name);
void			add_variable_to_env(char *name, char *value, t_env **our_env);
void			export_var(char *variable, t_env **our_env, int to_join);
void			export_print(t_env *tmp);
int				built_export(char **cmd_args, t_env **our_env);
void			built_pwd(void);
int				built_unset(char **cmd_args, t_env **our_env);
void			built_exit(char **args);
void			print_exit_error(char *arg, char *reason);
int				is_it_numeric_args(char *arg);
t_env			*find_variable(t_env **our_env, char *variable);
char			*get_variable_name(char *parsed_line);
char			*get_variable_value(char *parsed_line);
void			delete_var_env(t_env **our_env, t_env *var_to_delete);
void			update_env_pwd(t_env **our_env, char *new_value);
char			**convert_env_to_matrix(t_env *our_env);
int				is_it_builtin(char **cmd);
int				excute_builtins(char **cmd, t_env **our_env);
void			shell_level(t_main *v_main);

/****************redirections****************/

int				out_redirection(char *file_path);
int				in_redirection(char *file_path);
int				append_redirection(char *file_path);
int				handel_redirections(t_command *cmd);

/****************excution****************/

void			excute_cmd(t_main *v_main, t_command *cmd);
void			dup_close(int main_fd, int sec_fd, int origin_fd);
void			run_simple_cmd(t_main *main);
void			run_multi_cmd(t_main *v_main);
char			*get_cmd(char **paths, char *cmd);
char			*find_cmd_path(t_env **our_env, char *cmd);
int				simple_command(t_main *v_main);
int				list_cmd_size(t_command *cmd);
void			collect_libft_readline(void *to_collect);
void			heredoc_signal(void);
void			print_error(char *arg, char *cmd, char *reason);

/********************handling signals*****************/

void			ft_sig_handler(int sig);
void			handle_signal(void);
void			handle_heredoc(int sig);
void			heredoc_signal(void);

#endif
