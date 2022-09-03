/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_multi_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:45:30 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/03 14:24:47 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	excute_cmd(t_main *v_main, t_command *cmd)
{
	char *path;
	char **env;
	handel_redirections(cmd);
	if (is_it_builtin(cmd->command))
	{
		excute_builtins(cmd->command, &v_main->h_env);
		exit(0);
		
	} 
	path = find_cmd_path(&v_main->h_env, cmd->command[0]);
	env = convert_env_to_matrix(v_main->h_env);
	execve(path, cmd->command, env);
	print_error(cmd->command[1], cmd->command[0], ": command not found");
	exit(127);
}

void    dup_close(int main_fd, int sec_fd, int origin_fd)
{
    close(origin_fd);
    dup2(main_fd, origin_fd);
    close(main_fd);
    close(sec_fd);
}
void	handel_wait_exit(t_command *head)
{
	int	status;

	status = 0;
	while (head)
	{
		waitpid(head->pid, &status, 0);
		if (WIFEXITED(status))
			g_global.exist_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global.exist_status = WTERMSIG(status) + 128;
		else
			g_global.exist_status = 1;
		head = head->next;
	}
}

void	run_multi_cmd(t_main *v_main)
{
	int fd[2];
	t_command *head;

	head = v_main->cmd;
	while (head)
	{
		if (head->next)
			pipe(fd);
		g_global.catch_signal = 1;
		head->pid = fork();
		if (head->pid == 0)
		{
			if (head->next)
                dup_close(fd[1], fd[0], 1);
			excute_cmd(v_main, head);
		}
		else
            dup_close(fd[0], fd[1], 0 );
		head = head->next;
	}
	head = v_main->cmd;
	handel_wait_exit(head);
}