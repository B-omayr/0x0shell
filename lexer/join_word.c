/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:00:17 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/01 15:47:28 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	delete_space_token(t_tokens_list *head)
{
	t_tokens_list	*current;
	t_tokens_list	*temp;

	current = head;
	while (current->type != ENEWLINE)
	{
		if (current->next->type == ESPACE)
		{
			if (current->next->next->type == ESPACE)
			{
				temp = current->next;
				current->next = temp->next;
				//free(temp->value);
				//free(temp);
			}
			temp = current->next;
			current->next = temp->next;
			//free(temp->value);
			//free(temp);
		}
		current = current->next;
	}
	return (0);
}

int	join_word(t_tokens_list *head)
{
	t_tokens_list	*current;
	t_tokens_list	*temp;
	char			*str;
	int				len;

	current = head;
	while (current != NULL)
	{
		if (current->type == WORD && current->next->type == WORD)
		{
			len = get_lenght(current->value, '\0')
				+ get_lenght(current->next->value, '\0') + 1;
			str = ft_malloc(sizeof(char) * len + 1);
			str = ft_strjoin1(current->value, current->next->value);
			temp = current->next;
			current->value = str;
			current->next = temp->next;
			////free(temp->value);
			//free(temp);
		}
		else
		current = current->next;
	}
	return (0);
}
