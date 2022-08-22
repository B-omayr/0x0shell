/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:05:06 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/22 10:01:49 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *quotes_after_quotes(char *ln, int *index, char type)
{
	int i;

	i = *index;
	if (ln[i] == '"' && ln[i + 1] == type)
	{
		*index += 2;
		return ("");
	}
	else if (ln[i] == '\'' && ln[i + 1] == type)
	{
		*index += 2;
		return ("");
	}
	return (NULL);
}

int find_even_quotes(char *ln, int *index, char type)
{
	int i;
	int count;

	i = *index;
	count = 0;
	while (ln[i])
	{
		if (ln[i] == type)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	else if (count % 2 != 0)
	{
		printf("\e[0;31mThe problem come from your quotes");
		exit(1);
	} 
	return (0);
}

int len_inside_quotes(int i, char *ln, char type)
{
	int j;
	
	j = 0;
	while (ln[++i] != type)
		j++;
	return (j);
}

char *get_inside_quotes(char *ln, int *index, char type, t_main *v_main)
{
	char *token;
	int len;
	int i;
	int j;

	j = 0;
	i = *index;
	len = len_inside_quotes(i, ln, type);
	token = malloc(sizeof(char) * len + 1);
	while (ln[++i] != type)
		token[j++] = ln[i];
	i++;
	token[j] = '\0';
	puts(token);
	if (type == '"')
		while (search_for_dollar(token) == 1)
			expand_dollar(&token, v_main);	
	*index = i;
	return (token);
}

char	*treat_quotes(int *index, char *ln, t_main *v_main)
{
	char *temp;
	int i;

	i = *index;
	if (find_even_quotes(ln, &i, ln[i]))
	{
		if ((temp = quotes_after_quotes(ln, &i, ln[i])))
		{
			*index = i;
			return (temp);
		}
		else
		{
			temp = get_inside_quotes(ln, &i, ln[i], v_main);
			*index = i;
			return (temp);
		}
	}
	return (NULL);
}