/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utiles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:57:32 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/21 17:30:14 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int alpha_numeric(char c)
{
	if (!c)
		return (0);
	if ((c >= 0 && c <= 9) || (c >= 'a' && c <= 'z') 
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int search_for_dollar(char *token)
{
	int i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
			return (1);	
		i++;
	}
	return (0);
}

int dollar_name_len(char **token)
{
	bool x;
	int len;
	int i;

	len = 0;
	i = 0;
	x = true;
	while ((*token)[i] != '\0' && x == true)
	{
		if ((*token)[i] == '$')
		{
			while (alpha_numeric((*token)[++i]) == 1)
				len++;
		}	
		x = false;
		i++;
	}
	return (len);
}

void	get_after_dollar(char **token, int	*index, char **d_name)
{
	int i;
	int j;

	i = *index + 1;
	j = 0;
	while (alpha_numeric((*token)[i]))
		(*d_name)[j++] = (*token)[i++];
	(*d_name)[j] = '\0';
	*index = i;
}