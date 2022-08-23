/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:34:23 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/20 13:34:40 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *create_first_node(char *Name, char *Value)
{
    t_env   *first_env_node;

    first_env_node = malloc(sizeof(t_env));
    first_env_node->name = Name;
    first_env_node->value = Value;
    first_env_node->next = NULL;
    return (first_env_node);
}

void add_env_node(t_env *p_env, char *Name, char *Value)
{
    t_env *temp;
    
    temp = p_env;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = malloc(sizeof(t_env));
    temp->next->name = Name;
    temp->next->value = Value;
    temp->next->next =  NULL;
}

char *get_s1(char *env, char **str, int i)
{
	int j;

	j = -1;
	if (env[i] == '\0')
		free(str[1]);
	else if (env[i] == '=' && env[i + 1] == '\0')
		str[1][i] = '\0';
	else if (env[i] == '=' && env[i + 1] != '\0')
    {
        while(env[++i] != '\0')
			str[1][++j] = env[i];
    }	
	str[1][i] = '\0';
	return (str[1]);
}

t_env *create_env_list(t_env *h_env, char **env)
{
    char **str;
    int i;

    i = 0;
    if (env[0])
    {
        str = ft_split(env[0]);
        h_env = create_first_node(str[0], str[1]);
        free(str);
    }
    while (env[++i])
    {
        str = ft_split(env[i]);
        add_env_node(h_env, str[0], str[1]);
        free(str);
    }
    return (h_env);
}

void ft_initialize_env(t_main *var, int ac, char **av, char **env)
{
    (void) ac;
    (void) av;
    var->h_env = NULL;
    var->h_env = create_env_list(var->h_env, env);
}