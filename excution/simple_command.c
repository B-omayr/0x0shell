/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:43:25 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 13:02:39 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_level(t_main *v_main)
{
	t_env	*var_tmp;
	char	*tmp;

	var_tmp = find_variable(&v_main->h_env, "SHLVL");
	g_global.shel_level = ft_atoi(var_tmp->value);
	g_global.shel_level++;
	tmp = ft_strjoin("SHLVL=", ft_itoa(g_global.shel_level));
	export_var(tmp, &v_main->h_env, 0);
}

void	run_simple_cmd(t_main *main)
{
	char	*path;
	char	**env;

	path = find_cmd_path(&main->h_env, main->cmd->command[0]);
	env = convert_env_to_matrix(main->h_env);
	execve(path, main->cmd->command, env);
	print_error(main->cmd->command[1], main->cmd->command[0], \
		": command not found");
	exit(127);
}

int	simple_command(t_main *v_main)
{
	int	pid;
	int	status;

	if (handel_redirections(v_main->cmd) < 0)
		return (1);
	if (v_main->cmd->command)
	{
		if (is_it_builtin(v_main->cmd->command))
			return (excute_builtins(v_main->cmd->command, &v_main->h_env));
		if (!ft_strncmp(v_main->cmd->command[0], "./minishell", 12))
			shell_level(v_main);
		g_global.catch_signal = 1;
		pid = fork();
		if (pid == 0)
			run_simple_cmd(v_main);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_global.exist_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global.exist_status = WTERMSIG(status) + 128;
		else
			g_global.exist_status = 1;
	}
	return (0);
}
