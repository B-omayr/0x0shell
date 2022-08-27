/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:13:49 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/27 15:54:12 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (!access(cmd, X_OK | F_OK))
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, X_OK | F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	*find_cmd_path(t_env **our_env, char *cmd)
{
	char **paths;
	t_env *path;

	path = find_variable(our_env, "PATH");
	paths = ft_split(path->value, ':');
	if (!paths)
		return (NULL);
	return (get_cmd(paths, cmd));
}

void    run_simple_cmd(t_main *main)
{
	char *path;
	char **env;

	path = find_cmd_path(&main->h_env, main->cmd->command[0]);
	env = convert_env_to_matrix(main->h_env);
	execve(path, main->cmd->command, env);
	perror(main->cmd->command[0]);
	exit(1);
}

int simple_command(t_main *v_main)
{
	int pid;
	handel_redirections(v_main->cmd);
	if (v_main->cmd->command)
	{
		if (is_it_builtin(v_main->cmd->command))
			return (excute_builtins(v_main->cmd->command, &v_main->h_env));
		pid = fork();
		if (pid == 0)
			run_simple_cmd(v_main);  
		waitpid(pid, 0, 0);
	}
	return (0);
}

void	excute_cmd(t_main *v_main)
{
	char *path;
	char **env;
	handel_redirections(v_main->cmd);
	path = find_cmd_path(&v_main->h_env, v_main->cmd->command[0]);
	env = convert_env_to_matrix(v_main->h_env);
	execve(path, v_main->cmd->command, env);
}

int	list_cmd_size(t_command *cmd)
{
	 t_command *tmp;
	 int size;
	
	tmp = cmd;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	run_multi_cmd(t_main *v_main)
{
	int pid;
	int fd[2];
	int cmds_nbr;

	cmds_nbr = list_cmd_size(v_main->cmd);
	while (v_main->cmd)
	{
		if (v_main->cmd->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (v_main->cmd->next)
			{
				close(1);
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			excute_cmd(v_main);
		}
		else
		{
			close(0);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
		}
		v_main->cmd = v_main->cmd->next;
	}
	while (cmds_nbr)
	{
		waitpid(-1, NULL, 0);
		cmds_nbr--;
	}
}
