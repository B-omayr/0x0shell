/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:07:19 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/04 11:24:46 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute(t_main *v_main)
{
	add_history(v_main->line);
	v_main->list = ft_lexer(v_main->line, v_main);
	if (!check_syntax(v_main->list, v_main))
	{
		v_main->cmd = ft_parse(v_main->list, v_main->h_env);
		g_global.exist_status = 0;
		if (list_cmd_size(v_main->cmd) == 1)
			simple_command(v_main);
		else if (list_cmd_size(v_main->cmd) > 1)
			run_multi_cmd(v_main);
	}
	g_global.quotes_count = 0;
}

int	main(int ac, char **av, char **env)
{
	t_main	v_main;
	int		io[2];

	io[0] = dup(0);
	io[1] = dup(1);
	ft_initialize_env(&v_main, ac, av, env);
	while (1)
	{
		g_global.skip = 0;
		dup2(io[0], 0);
		dup2(io[1], 1);
		handle_signal();
		g_global.catch_signal = 0;
		v_main.line = readline(PROMPT);
		g_global.tmp_readline = v_main.line;
		collect_libft_readline(v_main.line);
		if (v_main.line == NULL)
			break ;
		execute(&v_main);
	}
	free_list(g_global.free_collect);
	close(io[0]);
	close(io[1]);
	return (0);
}
