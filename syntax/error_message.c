/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:07:57 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/23 09:09:25 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void display_message(char *value)
{
    printf("\e[7;91mMy_Minishell: syntax error near");
	printf(" unexpected token '%s'\e[0m\n", value);
}

void destroy_list(t_tokens_list *list)
{
    t_tokens_list   *temp;
    
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp->value);
        free(temp);
        temp = NULL;
    }
    free(list);
    list = NULL;
}