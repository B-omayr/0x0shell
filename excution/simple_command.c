/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:43:25 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/02 12:30:20 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    run_simple_cmd(t_main *main)
{
	char *path;
	char **env;

	path = find_cmd_path(&main->h_env, main->cmd->command[0]);
	env = convert_env_to_matrix(main->h_env);
	execve(path, main->cmd->command, env);
	perror("lala");
	exit(g_global.exist_status);
}

int simple_command(t_main *v_main)
{
	int pid;

	if (handel_redirections(v_main->cmd) < 0)
        return (1);
	if (v_main->cmd->command)
	{
		if (is_it_builtin(v_main->cmd->command))
			return (excute_builtins(v_main->cmd->command, &v_main->h_env));
		g_global.catch_signal = 1;
		pid = fork();
		if (pid == 0)
			run_simple_cmd(v_main);  
		waitpid(pid, 0, 0);
	}
	return (g_global.exist_status);
}
