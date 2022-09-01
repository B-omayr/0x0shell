/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utiles1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:08:15 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/01 12:05:29 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*last_part_here(char **token, int *index)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	i = *index;
	len = 0;
	j = 0;
	while ((*token)[i++])
		len++;
	res = ft_malloc(sizeof(char) * len + 1);
	i = *index;
	while ((*token)[i])
		res[j++] = (*token)[i++];
	res[j] = '\0';
	return (res);
}

char	*take_last_part_here(char **token, int *i)
{
	char	*ptr;
	int		index;

	index = *i;
	while ((*token)[index] == '$')
		index++;
	if ((*token)[index] == '?')
	{
		ptr = ft_strjoin1(ft_itoa(g_global.exist_status), &(*token)[++index]);
		return (ptr);
	}
	while ((*token)[index] != '\0')
	{
		if (!alpha_numeric((*token)[index]))
		{
			ptr = last_part_here(token, &index);
			return (ptr);
		}
		index++;
	}
	return (NULL);
}
