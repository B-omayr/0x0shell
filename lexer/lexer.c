/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:37:48 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/31 17:08:32 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token_node(t_tokens_list *var, int type, char *value)
{
	t_tokens_list	*temp;

	temp = var;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_tokens_list));
	temp->next->type = type;
	temp->next->value = value;
	temp->next->next = NULL;
}

t_tokens_list	*initialize_lst(void)
{
	t_tokens_list	*first_token;

	first_token = malloc(sizeof(t_tokens_list));
	first_token->type = NONE;
	first_token->value = ft_strdup1("NONE");
	first_token->next = NULL;
	return (first_token);
}

char	*take_word(char *ln, int *index)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	i = *index;
	j = 0;
	len = 1;
	while (ln[i] != '\0' && (ft_strchr1("|> \"<'", ln[i])) == NULL)
	{
		len++;
		i++;
	}
	i = *index;
	temp = malloc(sizeof(char) * len + 1);
	while (ln[i] && (ft_strchr1("|> \"<'", ln[i])) == NULL)
		temp[j++] = ln[i++];
	temp[j] = '\0';
	*index = i;
	return (temp);
}

char	*get_word(char *ln, int *index, t_main *v_main)
{
	char	*token;
	int		i;

	i = *index;
	token = NULL;
	while (ln[i] && ln[i] != '\n' && (ft_strchr1("|> <", ln[i])) == NULL)
	{
		if (ln[i] == '\'' || ln[i] == '"')
		{
			token = treat_quotes(&i, ln, v_main);
			*index = i;
			return (token);
		}
		else
		{
			token = take_word(ln, &i);
			while (search_for_dollar(token) == 1)
				expand_dollar(&token, v_main);
			*index = i;
			return (token);
		}
	}
	return (token);
}

t_tokens_list	*ft_lexer(char *ln, t_main *v_main)
{
	t_lexer			lexer;
	t_tokens_list	*var;

	lexer.i = 0;
	var = initialize_lst();
	while (ln[lexer.i])
	{
		lexer.token = ft_strdup1("");
		lexer.temp = lexer.token;
		if (lexer.i == 0)
			while (ln[lexer.i] == '\t' || ln[lexer.i] == ' ')
				lexer.i++;
		if (ln[lexer.i] == '|' || ln[lexer.i] == '>' || ln[lexer.i] == '<'
			|| ln[lexer.i] == ' ' || ln[lexer.i] == '\t')
			get_symbol(var, ln, &lexer.i, v_main);
		free (lexer.temp);
		if (ln[lexer.i] && (ft_strchr1("|> <", ln[lexer.i])) == NULL)
			lexer.token = get_word(ln, &lexer.i, v_main);
		if (ft_strcmp(lexer.token, "") != 0)
			add_token_node(var, WORD, lexer.token);
	}
	add_token_node(var, ENEWLINE, ft_strdup1("ENEWLINE"));
	join_word(var);
	delete_space_token(var);
	return (var);
}
