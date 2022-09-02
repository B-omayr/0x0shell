/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:38:07 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/02 17:01:52 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	malloc_cmd_arg(t_parse *var)
{
	t_tokens_list	*token;
	int				i;

	i = 0;
	token = var->current_token;
	var->cmd_arg = ft_malloc(sizeof(char *) * var->size + 1);
	while (i < var->size)
	{
		if (token->type == WORD)
			var->cmd_arg[i++] = ft_strdup1(token->value);
		if (token->type == REDIR_GREATER || token->type == REDIR_LESSER
			|| token->type == DOUBLE_GREATER || token->type == DOUBLE_LESSER)
			token = token->next;
		token = token->next;
	}
	var->cmd_arg[i] = NULL;
}

void	get_cmd_arg(t_parse *var)
{
	t_tokens_list	*token;
	int				i;

	var->cmd_arg = NULL;
	var->size = 0;
	i = 0;
	token = var->current_token;
	while (token->type != PIPE
		&& token->type != ENEWLINE)
	{
		if (token->type == WORD)
			var->size++;
		if (token->type == REDIR_GREATER || token->type == REDIR_LESSER
			|| token->type == DOUBLE_GREATER || token->type == DOUBLE_LESSER)
			token = token->next;
		token = token->next;
	}
	malloc_cmd_arg(var);
}

int	ft_strcmp_int(int x, int y)
{
	return (x - y);
}

void	initialize_var(t_parse *var, t_tokens_list *tokens_list)
{
	var->current_token = tokens_list;
	var->redirections = NULL;
	var->cmd_arg = NULL;
	var->cmd = NULL;
	var->size = 0;
}

int	arg_size(char **cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[i] != NULL)
		i++;
	return (i);
}
