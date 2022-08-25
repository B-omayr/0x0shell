/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:38:07 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/24 09:56:01 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strcmp_int(int x, int y)
{
    return (x - y);
}

void initialize_var(t_parse *var, t_tokens_list *tokens_list)
{
    var->current_token = tokens_list;
    var->redirections = NULL;
    var->cmd_arg = NULL;
    var->cmd = NULL;
    var->size = 0;
}

int arg_size(char **cmd_arg)
{
    int i;

    i = 0;
    while (cmd_arg[i] != NULL)
        i++;
    return (i);
}
