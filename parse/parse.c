/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 10:46:11 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/28 14:31:20 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command *first_cmd(char **cmd_arg, t_redirection *redirections)
{
    t_command *first_cmd;
    int size;
    int i;

    i = 0;
    first_cmd = malloc(sizeof(t_command));
    if (cmd_arg != NULL)
    {
        size = arg_size(cmd_arg);
        first_cmd->command = malloc(sizeof(char *) * size + 1);
        while (cmd_arg[i] != NULL)
        {
            first_cmd->command[i] = ft_strdup1(cmd_arg[i]);
            i++;
        }
        first_cmd->command[i] = NULL;
    }
    first_cmd->redirections = redirections;
    first_cmd->next = NULL;
    return (first_cmd);
}

void add_cmd(t_command *cmd, char **cmd_arg, t_redirection *redirections)
{
    t_command *new_cmd;
    int size;
    int i;

    i = 0;
    new_cmd = cmd;
    while (new_cmd->next != NULL)
        new_cmd = new_cmd->next;
    new_cmd->next = malloc(sizeof(t_command));
    new_cmd->next->command = NULL;
    if (cmd_arg != NULL)
    {
        size = arg_size(cmd_arg);
        new_cmd->next->command = malloc(sizeof(char *) * size + 1);
        while (cmd_arg[i] != NULL)
        {
            new_cmd->next->command[i] = ft_strdup1(cmd_arg[i]);
            i++;
        }
        new_cmd->next->command[i] = NULL;
    }
    new_cmd->next->redirections = redirections;
    new_cmd->next->next = NULL;
}

void set_cmd(t_parse *var)
{
    int i;

    i = 0;
    if (var->cmd == NULL)
    {
        var->cmd = first_cmd(var->cmd_arg, var->redirections);
        while (i < var->size)
            free(var->cmd_arg[i++]);
        free (var->cmd_arg);
        var->cmd_arg = NULL;
        var->redirections = NULL;
    }
    else
    {
        add_cmd(var->cmd, var->cmd_arg, var->redirections);
        while (i < var->size)
            free(var->cmd_arg[i++]);
        free (var->cmd_arg);
        var->cmd_arg = NULL;
        var->redirections = NULL;
    }
}

void    set_redirection(t_parse *var, t_tokens_list *token)
{
    t_redirection *redirection;
    t_redirection *temp;

    redirection = malloc(sizeof(t_redirection));
    redirection->type = token->type;
    redirection->f_name = token->next->value; // validate the syntax before this
    redirection->next = NULL;
    temp = var->redirections;
    if (!temp)
    {
        var->redirections = redirection;
        return ;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = redirection;   
}

t_command   *ft_parse(t_tokens_list *tokens_list, t_env *h_env)
{
    t_parse var;

    h_env = NULL;
    initialize_var(&var, tokens_list);
    while (var.current_token != NULL)
    {
        if (var.current_token->type == WORD && !var.cmd_arg)
            get_cmd_arg(&var);
        if (var.current_token->type == PIPE || var.current_token->type == ENEWLINE)
            set_cmd(&var);
        if (var.current_token->type == REDIR_GREATER || var.current_token->type == REDIR_LESSER
            || var.current_token->type == DOUBLE_GREATER || var.current_token->type == DOUBLE_LESSER)
        {
            set_redirection(&var, var.current_token);
            var.current_token = var.current_token->next;
        }
        var.current_token = var.current_token->next;
    }
    return (var.cmd);
}