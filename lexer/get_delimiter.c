/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:37:36 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/30 18:57:58 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int len_inside_quotes1(int i, char *ln, char type)
{
	int j;
	
	j = 0;
	while (ln[++i] != type)
		j++;
	return (j);
}

char *get_inside_quotes1(char *ln, int *index, char type)
{
	char *token;
	int len;
	int i;
	int j;

	j = 0;
	i = *index;
	len = len_inside_quotes1(i, ln, type);
	token = malloc(sizeof(char) * len + 1);
	while (ln[++i] != type)
		token[j++] = ln[i];
	i++;
	token[j] = '\0';
	*index = i;
	return (token);
}

char	*treat_quotes1(int *index, char *ln)
{
	char *temp;
	int i;

	i = *index;
	v_global.quotes_count = 0;

	if (find_even_quotes(ln, &i, ln[i]))
	{
		if (quotes_after_quotes(ln, &i, ln[i]))
		{
			i -= 2;
			temp = quotes_after_quotes(ln, &i, ln[i]);
			*index = i;
			return (temp);
		}
		else
		{
			temp = get_inside_quotes1(ln, &i, ln[i]);
			*index = i;
			return (temp);
		}
	}
	else
		*index = i;
	return (ft_strdup1(""));
}

char *set_delimiter_name(char *ln, int *index)
{
	char *temp;
	int len;
	int exp;
	int i;
	int j;

	exp = *index + 1;
	j = 0;
	len = 0;
	while (ln[exp] == ' ')
		exp++;
	i = exp;
	if ((ft_strchr1("|> <", ln[exp])) == NULL)
	{
		while (ln[exp] != '\0' && (ft_strchr1("|> <", ln[exp])) == NULL)
		{
			len++;
			exp++;
		}
		temp = malloc(sizeof(char) * len + 1);
		while (ln[i] && (ft_strchr1("|> <", ln[i])) == NULL)
			temp[j++] = ln[i++];
		temp[j] = '\0';
		*index = i;
	}
	else
		return (NULL);
	return (temp);
}


void get_delimitter(t_tokens_list *var, char *ln, int *index, t_main *v_main)
{
	int i = 0;
	char *d_name;
	char *token = NULL;
	char *temp;
	
	(void)v_main;
	d_name = set_delimiter_name(ln, index);
	if (check_quotess(d_name))
	{
		v_main->cmd->is_delimter_in_quotes = false;
		while (d_name[i])
		{
			if (d_name[i] == '\'' || d_name[i] == '"')
				temp = treat_quotes1(&i, d_name);
			else
				temp = take_word(d_name, &i);
			token = ft_strjoin1(token, temp);
			if (ft_strcmp(temp, "") != 0)
				free(temp);
		}
	}
	else
	{
		if (!d_name)
			return ;
		v_main->cmd->is_delimter_in_quotes = true;
		token = d_name;
	}
	add_token_node(var, WORD, token);
	get_token_ESPACE(var, ln, *index);
}