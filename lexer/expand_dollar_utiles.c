/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utiles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:57:32 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/26 12:47:46 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void check_dollar_even(char **token, int *index, t_main *v_main)
{
	int count;
	int i;

	i = *index;
	count = 0;
	while ((*token)[i++] == '$')
		count++;
	if (count % 2 != 0)
		v_main->dollar_type = true;
	else
		v_main->dollar_type = false;
}

char	*get_dollar_name(char **token, t_main *v_main)
{
	char *d_name;
	int len;
	bool x;
	int i;
	int j;
	
	i = 0;
	j = 0;
	x = true;
	len = dollar_name_len(token);
	d_name = malloc(sizeof(char) * len + 1);
	while ((*token)[i] != '\0' && x == true)
	{
		if ((*token)[i] == '$')
		{
			check_dollar_even(token, &i, v_main);
			get_after_dollar(token, &i, &d_name);					
			x = false;
		}		
		i++;
	}
	return (d_name);
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
			while ((*token)[i] == '$')
				i++;
			while (alpha_numeric((*token)[i++]) == 1)
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

	i = *index;
	j = 0;
	while ((*token)[i] == '$')
		i++;
	while (alpha_numeric((*token)[i]))
		(*d_name)[j++] = (*token)[i++];
	(*d_name)[j] = '\0';
	*index = i;
}