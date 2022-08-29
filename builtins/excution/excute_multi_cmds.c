/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_multi_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:45:30 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/29 11:52:43 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	excute_cmd(t_main *v_main)
{
	char *path;
	char **env;
	handel_redirections(v_main->cmd);
	path = find_cmd_path(&v_main->h_env, v_main->cmd->command[0]);
	env = convert_env_to_matrix(v_main->h_env);
	execve(path, v_main->cmd->command, env);
}

void    dup_close(int main_fd, int sec_fd, int origin_fd)
{
    close(origin_fd);
    dup2(main_fd, origin_fd);
    close(main_fd);
    close(sec_fd);
}

void	run_multi_cmd(t_main *v_main)
{
	int pid;
	int fd[2];
	int cmds_nbr;
/* trait case of existing file ND EXCUTABLE .*/
	cmds_nbr = list_cmd_size(v_main->cmd);
	while (v_main->cmd)
	{
		if (v_main->cmd->next)
			pipe(fd);
		v_global.catch_signal = 1;
		pid = fork();
		if (pid == 0)
		{
			if (v_main->cmd->next)
                dup_close(fd[1], fd[0], 1);
			excute_cmd(v_main);
		}
		else
            dup_close(fd[0], fd[1], 0);
		v_main->cmd = v_main->cmd->next;
	}
	while (cmds_nbr)
	{
		waitpid(-1, NULL, 0);
		cmds_nbr--;
	}
}