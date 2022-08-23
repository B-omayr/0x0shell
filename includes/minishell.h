/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:27:55 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/23 13:48:52 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>


#define PIPE 1
#define WORD 2
#define NONE 3
#define SPACE 4
#define REDIR_GREATER 5
#define REDIR_LESSER 6
#define DOUBLE_GREATER 7
#define DOUBLE_LESSER 8
#define NEWLINE 9

int quotes_count;

typedef enum e_type {
    e_pipe, 
    e_newline,
}	t_type;

typedef struct s_lexer{
    int i;
    char *token;
	char *temp;
}   t_lexer;

typedef struct s_tokens_list{
    int type;
    char *value;
    struct s_tokens_list *next; 
}   t_tokens_list;

typedef struct s_env{
    char *value;
    char *name;
    struct s_env *next;
} t_env;

typedef struct s_command{
    char **command;
    t_type separator;
    struct s_command *next;
} t_command;

typedef struct s_rediction{
    char *f_name;
    
} t_redirection;

typedef struct s_parse{
    t_tokens_list *current_token;
    t_command   *cmd;
    char **cmd_arg;
    int size;
} t_parse;

typedef struct s_main{
    t_tokens_list *list;
    t_command *cmd;
    t_env *h_env;
    char *line;
    bool type_dollar;
} t_main;


/****************libft Function****************/

char	**ft_split(char *env);
char	*ft_strdup(char *str);
int		get_lenght(char *ln, char c);
char	*ft_strchr(char *str, char c);
int		ft_strcmp(char *str, char *ptr);
int		lenght_of_word(char *ln, int *index);
char	*ft_strjoin(char *s1, char *s2);

/*****************env Function*****************/

void	ft_initialize_env(t_main *var, int ac, char **av, char **env);
t_env	*create_env_list(t_env *p_env, char **env);
void	add_env_node(t_env *p_env, char *Name, char *Value);
t_env	*create_first_node(char *Name, char *Value);
char	*get_s1(char *env, char **str, int i);

/****************lexer Function****************/

t_tokens_list *ft_lexer(char *line, t_main *v_main);
void get_symbol(t_tokens_list *var, char *ln, int *index);
void add_token_node(t_tokens_list *var, int type, char *value);
char *treat_quotes(int *index, char *ln, t_main *v_main);
int	expand_dollar(char **token, t_main *v_main);
int search_for_dollar(char *token);
int dollar_name_len(char **token);
void	get_after_dollar(char **token, int	*index, char **d_name);
void	get_inside_bracket(char **token, int *index, char **d_name);
int edit_token(char **token, t_main *v_main);
int	join_word(t_tokens_list *v_main);
int alpha_numeric(char c);
void check_dollar_even(char **token, int *index, t_main *v_main);
char	*get_dollar_name(char **token, t_main *v_main);

/****************syntax Function***************/

int	check_syntax(t_tokens_list *var);
void destroy_list(t_tokens_list *list);
void display_message(char *value);

/****************parse Function****************/

t_command   *ft_parse(t_tokens_list *tokens_list, t_env *h_env);
void initialize_var(t_parse *var, t_tokens_list *tokens_list);
int arg_size(char **cmd_arg);
int ft_strcmp_int(int x, int y);

#endif