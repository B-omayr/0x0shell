/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:07:57 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/01 15:49:33 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_message(char *value)
{
	printf("\e[7;91mMy_Minishell: syntax error near");
	printf(" unexpected token '%s'\e[0m\n", value);
}

void	destroy_list(t_tokens_list *list)
{
	// t_tokens_list	*temp;
	(void) list;
	// while (list != NULL)
	// {
	// 	temp = list;
	// 	list = list->next;
	// 	free(temp->value);
	// 	free(temp);
	// 	temp = NULL;
	// }
	// // free(list);
	// list = NULL;
}
