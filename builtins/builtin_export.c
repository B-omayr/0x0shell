/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:26:48 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 09:26:30 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validity_of_var_name(char *var_name)
{
	int	i;
	int	var_len;
	int	exit_status;

	i = 1;
	exit_status = 0;
	var_len = get_lenght(var_name, '=');
	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
		return (1);
	if (var_name[var_len] == '=' && var_name[var_len - 1] == '+')
		exit_status = 2;
	while (var_name[i] && var_name[i] != '=')
	{
		if (var_name[i] == '+' && var_name[i + 1] == '=')
		{
			i++;
			continue ;
		}
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (1);
		i++;
	}
	return (exit_status);
}

void	add_variable_to_env(char *name, char *value, t_env **our_env)
{
	t_env	*tmp_env;
	t_env	*add_new_var;

	tmp_env = *our_env;
	add_new_var = (t_env *)ft_malloc(sizeof(t_env));
	if (!add_new_var)
		return ;
	add_new_var->name = name;
	add_new_var->value = value;
	add_new_var->next = NULL;
	if (!(*our_env))
	{
		*our_env = add_new_var;
		return ;
	}
	while (tmp_env->next)
		tmp_env = tmp_env->next;
	tmp_env->next = add_new_var;
}

void	export_var(char *variable, t_env **our_env, int to_join)
{
	t_env	*tmp;
	char	*name;
	char	*value;

	name = get_variable_name(variable);
	value = get_variable_value(variable);
	tmp = find_variable(our_env, name);
	if (tmp)
	{
		if (value)
		{
			if (to_join > 0)
			{
				tmp->value = ft_strjoin(tmp->value, value);
				if (!tmp->value)
					tmp->value = ft_strdup(value);
			}
			else if (tmp->value)
			{
				tmp->value = ft_strdup(value);
			}
		}
	}
	else
		add_variable_to_env(name, value, our_env);
}

void	export_print(t_env *tmp)
{
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

int	built_export(char **cmd_args, t_env **our_env)
{
	t_env	*tmp;
	int		i;

	tmp = *our_env;
	i = 0;
	if (!cmd_args[1])
		export_print(tmp);
	else
	{
		cmd_args++;
		while (*cmd_args)
		{
			if (validity_of_var_name(*cmd_args) == 1)
			{
				g_global.exist_status = 1;
				print_error(*cmd_args, "export", \
					": not a valid identifier");
			}
			else
				export_var(*cmd_args, our_env, validity_of_var_name(*cmd_args));
			cmd_args++;
		}
	}
	return (g_global.exist_status);
}
