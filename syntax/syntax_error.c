/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:34:06 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/04 11:00:18 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error_none(t_tokens_list *token_none)
{
	int	ret;

	ret = 0;
	if (token_none->next->type == PIPE)
	{
		display_message(token_none->next->value);
		ret = 1;
	}
	else if (token_none->next->type == ENEWLINE)
		ret = 1;
	return (ret);
}

int	check_error_pipe(t_tokens_list *token_pipe)
{
	int	ret;

	ret = 0;
	if (token_pipe->next->type == PIPE || token_pipe->next->type == ENEWLINE)
	{
		display_message(token_pipe->next->value);
		ret = 1;
	}
	return (ret);
}

int	check_error_red(t_tokens_list *token_red)
{
	int	ret;

	ret = 0;
	if (token_red->next->type != WORD)
	{
		display_message(token_red->next->value);
		ret = 1;
	}
	return (ret);
}

int	check_errors(t_tokens_list *current)
{
	int	ret;

	ret = 0;
	if (g_global.quotes_count == 1)
	{
		printf("\e[7;91mThere is a problem came from your quotes\e[0m\n");
		ret = 1;
	}
	else if (current->type == NONE)
		ret = check_error_none(current);
	else if (current->type == PIPE)
		ret = check_error_pipe(current);
	else if (current->type == REDIR_GREATER || current->type == REDIR_LESSER
		|| current->type == DOUBLE_GREATER || current->type == DOUBLE_LESSER)
		ret = check_error_red(current);
	return (ret);
}

int	check_syntax(t_tokens_list *head, t_main *v_main)
{
	t_tokens_list	*temp;
	char			*tmp;

	temp = head;
	while (temp != NULL)
	{
		if (check_errors(temp))
			return (1);
		if (temp->type == DOUBLE_LESSER)
		{
			tmp = temp->next->value;
			temp->next->value = traite_herdoc(temp->next->value, v_main);
			if (g_global.skip)
				return (1);
			temp = temp->next;
		}
		temp = temp->next;
	}
	return (0);
}
