/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:15:05 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/31 09:04:16 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int  get_token_pipe(t_tokens_list *var, int i)
{
	char *token;

	token = ft_strdup1("|");
	add_token_node(var, PIPE, token);
	return (i);
}

int get_token_redir_greater(t_tokens_list *var, char *ln, int i)
{
	char *token;

	if (ln[i + 1] == '>')
	{
		token = ft_strdup1(">>");
		add_token_node(var, DOUBLE_GREATER, token);
		i++;
	}
	else
	{
		token = ft_strdup1(">");
		add_token_node(var, REDIR_GREATER, token);
	}
		
	return (i);
}

int	get_token_ESPACE(t_tokens_list *var, char *ln, int i)
{
	char *token;
	while (ln[i] == ' ' || ln[i] == '\t')
		i++;
	token = ft_strdup1(" ");
	add_token_node(var, ESPACE, token);
	return (i);
}

int get_token_redir_lesser(t_tokens_list *var, char *ln, int i, t_main *v_main)
{
	char *token;

	if (ln[i + 1] == '<')
	{
		token = ft_strdup1("<<");
		add_token_node(var, DOUBLE_LESSER, token);
		i++;
		get_delimitter(var, ln, &i, v_main);
		
	}
	else
	{
		token = ft_strdup1("<");
		add_token_node(var, REDIR_LESSER, token);
	}
	return (i);
}

void    get_symbol(t_tokens_list *var, char *ln, int *index, t_main *v_main)
{
	int i;

	i = *index;
	if (ln[i] == '|')
		i = get_token_pipe(var, i) + 1;
	if (ln[i] == '>')
		i = get_token_redir_greater(var, ln, i) + 1;
	if (ln[i] == '<')
		i = get_token_redir_lesser(var, ln, i, v_main) + 1;
	if (ln[i] == ' ' || ln[i] == '\t')
		i = get_token_ESPACE(var, ln, i);
	*index = i;
} 