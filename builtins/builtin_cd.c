/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:29:31 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/27 16:39:38 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int built_cd(char *path, t_env **our_env)
{
	t_env *oldpwd;
	t_env *currentpwd;
	t_env *home_pwd;

	
	currentpwd = find_variable(our_env, "PWD");
	if (!path || !ft_strncmp(path, "~", 1) )
	{
		home_pwd = find_variable(our_env, "HOME");
		if (!home_pwd)
		{
			perror("HOME");
			return (-1);
		}
		if (chdir(home_pwd->value) < 0)
			return (-1);
		update_env_pwd(our_env, getcwd(NULL, 0));
		return (0);
	}
	if (!ft_strncmp(path, "-", 2))
	{
		oldpwd = find_variable(our_env, "OLDPWD");
		if (!oldpwd)
		{
			perror("OLDPATH is unset");
			return (-1);
		}
		if (chdir(oldpwd->value) < 0)
			return (-1);
		update_env_pwd(our_env, getcwd(NULL, 0));
		built_pwd();
		return (0);
	}
	if (chdir(path) < 0)
		printf("bash: cd: %s: No such file or directory\n", path);
	update_env_pwd(our_env, getcwd(NULL, 0));
	return (0);
}