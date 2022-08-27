/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:07:19 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/27 16:22:00 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_type(int type) {
    if (type == REDIR_GREATER)
        return ">";
    if (type == REDIR_LESSER)
        return "<";
    if (type == DOUBLE_GREATER)
        return ">>";
    if (type == DOUBLE_LESSER)
        return "<<";
    return "ze";
}

// void	signal_handler(int sig_num)
// {
// 	if (sig_num == SIGINT)
// 	{
// 		(void)sig_num;
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

int main(int ac, char **av, char **env)
{
    t_main v_main;
    t_lexer *lexer;

    lexer = NULL;
    ft_initialize_env(&v_main, ac, av, env);
    while (1)
    {
        // rl_catch_signals = 0;
        signal(SIGQUIT, SIG_IGN);
        v_main.line = readline("\e[1;32m➜  \e[1;31mMini👽shell\e[1;33m ➤ \e[1;37m\e[m");
        if (v_main.line == NULL)
            return (0);
        add_history(v_main.line);
        v_main.list = ft_lexer(v_main.line, &v_main);
        if(v_main.list == NULL)
            return (0);
        if (!check_syntax(v_main.list))
        {
            v_main.cmd = ft_parse(v_main.list, v_main.h_env); /*You will work with this pointer*/
            while(v_main.cmd)
            {
                t_redirection *red = v_main.cmd->redirections;
                while (v_main.cmd->command && *(v_main.cmd->command)) {
                    printf("%s ", *(v_main.cmd->command));
                    (v_main.cmd->command)++;
                }
                while (red) {
                    printf("%s %s ", get_type(red->type), red->f_name);
                    red = red->next;
                }
                printf("\n");
                v_main.cmd = v_main.cmd->next;
            }
        }
        free(v_main.line);
    }
    return (0);
}