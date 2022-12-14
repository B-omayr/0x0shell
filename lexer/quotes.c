/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:05:06 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/01 13:04:47 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*quotes_after_quotes(char *ln, int *index, char type)
{
	int	i;

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

int	find_even_quotes(char *ln, int *index, char type)
{
	int	i;
	int	count;

	i = *index + 1;
	count = 0;
	while (ln[i])
	{
		if (ln[i] == type)
			return (1);
		i++;
	}
	*index = i;
	g_global.quotes_count = 1;
	return (0);
}

int	len_inside_quotes(int i, char *ln, char type)
{
	int	j;

	j = 0;
	while (ln[++i] != type)
		j++;
	return (j);
}

char	*get_inside_quotes(char *ln, int *index, char type, t_main *v_main)
{
	char	*token;
	int		len;
	int		i;
	int		j;

	j = 0;
	i = *index;
	len = len_inside_quotes(i, ln, type);
	token = ft_malloc(sizeof(char) * len + 1);
	while (ln[++i] != type)
		token[j++] = ln[i];
	i++;
	token[j] = '\0';
	if (type == '"')
		while (search_for_dollar(token) == 1)
			expand_dollar(&token, v_main);
	*index = i;
	return (token);
}

char	*treat_quotes(int *index, char *ln, t_main *v_main)
{
	char	*temp;
	int		i;

	i = *index;
	g_global.quotes_count = 0;
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
			temp = get_inside_quotes(ln, &i, ln[i], v_main);
			*index = i;
			return (temp);
		}
	}
	else
		*index = i;
	return (ft_strdup1(""));
}
