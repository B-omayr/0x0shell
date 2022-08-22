/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:07:19 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/22 11:31:08 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
    t_main v_main;
    t_lexer *lexer;

    lexer = NULL;
    ft_initialize_env(&v_main, ac, av, env);
    while (1)
    {
        v_main.line = readline("\e[1;32m➜  \e[1;31mMini👽shell\e[1;33m ➤ \e[1;37m\e[m");
        if (v_main.line == NULL)
            return (0);
        add_history(v_main.line);
        v_main.list = ft_lexer(v_main.line, &v_main);
        if(v_main.list == NULL)
            return (0);
        if (!check_syntax(v_main.list))
        {
            v_main.cmd = ft_parse(v_main.list, v_main.h_env);
        }
        // t_tokens_list *temp;
        // temp = v_main.list;
        // while (temp != NULL)
        // {
        //     printf("type : {%d}; Value : {%s}\n", temp->type, temp->value);
        //     temp = temp->next;
        // }
        
        t_command *temp;
        temp = v_main.cmd;
        int i = 0;
        int j = 0;
        
        while (temp != NULL)
        {
            i = 0;
            while (temp->command[i] != NULL)
            {
                printf("%d : arg : %s, %d\n",j, temp->command[i], temp->separator);
                i++;
            }
            j++;
            temp = temp->next;
        } 
    }
    return (0);
}