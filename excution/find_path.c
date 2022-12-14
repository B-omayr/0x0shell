/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:13:49 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 12:51:08 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
	{
		if (access(cmd, X_OK))
			return (NULL);
	}
	if (!access(cmd, X_OK | F_OK))
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, X_OK | F_OK) == 0)
			return (command);
		paths++;
	}
	return (NULL);
}

char	*find_cmd_path(t_env **our_env, char *cmd)
{
	char	**paths;
	t_env	*path;

	path = find_variable(our_env, "PATH");
	if (!path)
	{
		print_error(cmd, " ", \
		": command not found");
		exit(127);
	}
	paths = ft_split(path->value, ':');
	if (!paths)
		return (NULL);
	return (get_cmd(paths, cmd));
}
