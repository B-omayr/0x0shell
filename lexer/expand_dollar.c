/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:23:11 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/22 10:52:31 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_dollar_name(char **token)
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
			get_after_dollar(token, &i, &d_name);					
			x = false;
		}		
		i++;
	}
	return (d_name);
}

char	*last_part_here(char **token, int *index)
{
    char *res;
    int len;
	int i;
	int j;

    i = *index;
    len = 0;
	j = 0;
    while ((*token)[i++])
        len++;
	res = malloc(sizeof(char) * len + 1);
	i = *index;
	while ((*token)[i])
		res[j++] = (*token)[i++];
	res[j] = '\0';
	return (res);
}

char	*get_last_part(char **token)
{
	char *ptr;
	int index;

	index = 0;
	while ((*token)[index])
    {
		if ((*token)[index] == '$')
		{
			index++;
            while ((*token)[index] != '\0')
            {
                if (!alpha_numeric((*token)[index]))
				{
                	ptr = last_part_here(token, &index);
					return (ptr);
				}
                index++;
            }
        }
        index++;
    }
	return (NULL);
}

char	*join_token(char **token, char *d_value)
{
	char *temp;
	char *res;
	char *ret;
	int len;
	int i;

	i = 0;
	len = get_lenght((*token), '$');
	temp = malloc(sizeof(char) * len + 1);	
	while ((*token)[i] != '$')
	{
		temp[i] = (*token)[i];
		i++;
	}
	temp[i] = '\0';
	res = ft_strjoin(temp, d_value);
	temp = get_last_part(token);
	ret = ft_strjoin(res, temp);
	free(temp);
	return (ret);
}


int	expand_dollar(char **token, t_main *v_main)
{
	t_env *temp;
	char *d_name;
	char *d_value;

	temp = v_main->h_env;
	d_name = get_dollar_name(token);
	while (temp != NULL)
	{
		if (!ft_strcmp(d_name, temp->name))
		{
			d_value = temp->value;
			free(d_name);
			*token = join_token(token, d_value);
			return (0);
		}
		else if (temp->next == NULL && (ft_strcmp(d_name, temp->name)) != 0)
		{
			free(d_name);
			d_value = NULL;
			*token = join_token(token, d_value);
		}
		temp = temp->next;
	}
	return (0);
}