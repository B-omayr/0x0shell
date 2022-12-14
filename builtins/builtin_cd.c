/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:29:31 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 09:24:54 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	home_cwd(char *path, t_env **our_env)
{
	t_env	*home_pwd;

	if (!path || !ft_strncmp(path, "~", 1))
	{
		home_pwd = find_variable(our_env, "HOME");
		if (!home_pwd)
		{
			perror("OLDPATH is unset");
			g_global.exist_status = 1;
			return (1);
		}
		if (chdir(home_pwd->value) < 0)
		{
			g_global.exist_status = 1;
			return (1);
		}
		update_env_pwd(our_env, getcwd(NULL, 0));
		return (0);
	}
	return (-1);
}

int	cd_dash(char *path, t_env **our_env)
{
	t_env	*oldpwd;

	if (!ft_strncmp(path, "-", 2))
	{
		oldpwd = find_variable(our_env, "OLDPWD");
		if (!oldpwd)
		{
			perror("OLDPATH is unset");
			g_global.exist_status = 1;
			return (1);
		}
		if (chdir(oldpwd->value) < 0)
		{
			g_global.exist_status = 1;
			return (1);
		}
		update_env_pwd(our_env, getcwd(NULL, 0));
		built_pwd();
		return (0);
	}
	return (-1);
}

int	built_cd(char *path, t_env **our_env)
{
	if (home_cwd(path, our_env) >= 0)
		return (g_global.exist_status);
	if (cd_dash(path, our_env) >= 0)
		return (g_global.exist_status);
	if (chdir(path) < 0)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		return (1);
	}
	update_env_pwd(our_env, getcwd(NULL, 0));
	return (0);
}
