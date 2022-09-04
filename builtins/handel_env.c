/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:25:23 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 09:34:39 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*find_variable(t_env **our_env, char *variable)
{
	t_env	*tmp_var;
	size_t	variable_lenght;

	variable_lenght = ft_strlen(variable);
	tmp_var = *our_env;
	while (tmp_var)
	{
		if (!ft_strncmp(tmp_var->name, variable, variable_lenght + 1))
			return (tmp_var);
		tmp_var = tmp_var->next;
	}
	return (NULL);
}

char	*get_variable_name(char *parsed_line)
{
	char	*var_name;
	int		plus;

	plus = 0;
	var_name = ft_strchr(parsed_line, '=');
	plus = validity_of_var_name(parsed_line);
	if (var_name && !plus)
		var_name = ft_substr(parsed_line, 0, var_name - parsed_line);
	else if (var_name && plus > 0)
		var_name = ft_substr(parsed_line, 0, var_name - parsed_line - 1);
	else if (!var_name)
		var_name = ft_substr(parsed_line, 0, ft_strlen(parsed_line) + 1);
	if (!var_name)
		return (NULL);
	return (var_name);
}

char	*get_variable_value(char *parsed_line)
{
	char	*var_value;

	var_value = ft_strchr(parsed_line, '=');
	if (!var_value)
		return (NULL);
	if (var_value)
		var_value = ft_substr(parsed_line, var_value - parsed_line + 1, \
			ft_strlen(var_value) + 1);
	if (!var_value)
		return (0);
	return (var_value);
}

void	delete_var_env(t_env **our_env, t_env *var_to_delete)
{
	t_env	*tmp;

	tmp = *our_env;
	if (tmp == var_to_delete)
		*our_env = tmp->next;
	else
	{
		while (tmp->next != var_to_delete)
			tmp = tmp->next;
		tmp->next = var_to_delete->next;
	}
}

void	update_env_pwd(t_env **our_env, char *new_value)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_variable(our_env, "PWD");
	oldpwd = find_variable(our_env, "OLDPWD");
	if (oldpwd && pwd)
	{
		oldpwd->value = pwd->value;
		pwd->value = new_value;
	}
	else if (pwd)
		pwd->value = new_value;
}
