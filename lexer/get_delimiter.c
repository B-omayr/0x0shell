/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delimiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:37:36 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/25 16:40:18 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *set_delimiter(char *ln, int *index)
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
	return (temp);
}

void get_delimitter(t_tokens_list *var, char *ln, int *index)
{
	char *token;
	token = set_delimiter(ln, index);
	add_token_node(var, WORD, token);
	get_token_space(var, ln, *index);
}