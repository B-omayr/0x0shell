/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:23:11 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/30 16:56:45 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			while ((*token)[index] == '$')
				index++;
			if ((*token)[index] == '?')
			{
				ptr = ft_strjoin1(ft_itoa(v_global.exist_status), &(*token)[++index]);
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
	res = ft_strjoin1(temp, d_value);
	temp = get_last_part(token);
	ret = ft_strjoin1(res, temp);
	free(temp);
	return (ret);
}

char	*set_value(char *d_value, char *d_name, char **token, t_main *v_main)
{
	if (v_main->dollar_type == true)
		*token = join_token(token, d_value);
	else if (v_main->dollar_type == false)
		*token = join_token(token, d_name);
	return (0);	
}

int	expand_dollar(char **token, t_main *v_main)
{
	t_env *temp;
	char *d_name;

	temp = v_main->h_env;
	d_name = get_dollar_name(token, v_main);
	while (temp != NULL)
	{
		if (!ft_strcmp(d_name, temp->name))
		{
			set_value(temp->value, d_name, token, v_main);
			free(d_name);
			return (0);
		}	
		else if (temp->next == NULL && (ft_strcmp(d_name, temp->name)) != 0)
		{
			if (v_main->dollar_type == false)
				*token = join_token(token, d_name);
			else 
				*token = join_token(token, NULL);
			free(d_name);	
		}
		temp = temp->next;
	}
	return (0);
}