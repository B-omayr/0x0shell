/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:07:19 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/31 16:08:29 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_sig_handler(int sig)
{
	if (sig == 3)
	{
		if (g_global.catch_signal ==  1 && ft_strncmp(g_global.tmp_readline, "./minishell", 11))
			printf("Quit : 3\n");
		else if (g_global.catch_signal == 0)
			rl_replace_line("", 0);
	}	
	if (sig == 2)
	{
		if (g_global.catch_signal == 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_global.catch_signal == 1 && ft_strncmp(g_global.tmp_readline, "./minishell", 11))
			printf("\n");
	}
}

void handle_signal(void)
{
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
}

int main(int ac, char **av, char **env)
{
	t_main v_main;
	t_lexer *lexer;
	int     IO[2];

	IO[0] = dup(0);
	IO[1] = dup(1);
	lexer = NULL;
	ft_initialize_env(&v_main, ac, av, env);
	while (1)
	{
		dup2(IO[0], 0);
		dup2(IO[1], 1);
		handle_signal();
		g_global.catch_signal = 0;
		v_main.line = readline("\e[1;32m➜  \e[1;31mMini👽shell\e[1;33m ➤ \e[1;37m\e[m");
		g_global.tmp_readline = v_main.line;
		if (v_main.line == NULL)
			return (printf("\033[17C\033[1A exit\n"), 0);
		add_history(v_main.line);
		v_main.list = ft_lexer(v_main.line, &v_main);
		if(v_main.list == NULL)
			return (0);
		if (!check_syntax(v_main.list, &v_main))
		{
			v_main.cmd = ft_parse(v_main.list, v_main.h_env);
			if (list_cmd_size(v_main.cmd) == 1)
				simple_command(&v_main);
			else if (list_cmd_size(v_main.cmd) > 1) 
				run_multi_cmd(&v_main);
		}
		g_global.quotes_count = 0;
		free(v_main.line);
	}
	close(IO[0]);
	close(IO[1]);
	return (0);
}