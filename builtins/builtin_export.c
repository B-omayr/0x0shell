/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:26:48 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/27 17:43:33 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validity_of_var_name(char *var_name)
{
	int i;
    int var_len;
	int exit_status = 0;
	i = 1;
	puts("\nhere");
	printf("%s\n", var_name);
	fflush(stdout);
    var_len = get_lenght(var_name, '=');
	puts("\nhere");
	if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
		return (-1);
	if (var_name[var_len] == '=' && var_name[var_len - 1] == '+')
	{
		// printf("%c", var_name[var_len]);
		exit_status = 2;
	}
	while (var_name[i] && var_name[i] != '=')
	{
		if (var_name[i] == '+' && var_name[i + 1] == '=')
		{
			i++;
			continue;
		}
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (-1);
		i++;
	}
	printf("exit status: %d\n", exit_status);
	puts("here2");
	return (exit_status);
}

void	add_variable_to_env(char *name, char *value, t_env **our_env)
{
	t_env	*tmp_env;
	t_env	*add_new_var;

	tmp_env = *our_env;
	add_new_var = (t_env *)malloc(sizeof(t_env));
	if (!add_new_var)
		exit(-1);
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
	t_env *tmp;
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
				if(!tmp->value)
					tmp->value = ft_strdup(value);
				printf("hahah %s", tmp->value);
			}
			else if (tmp->value && to_join == 0)
			{
				free(tmp->value);
				tmp->value = value;
			}
		}
		free(name);
	}
	else
		add_variable_to_env(name, value, our_env);
}

int	built_export(char **cmd_args, t_env **our_env)
{
	t_env *tmp;
	int		exit_status = 0;

	tmp = *our_env;
	// printf("ss");
	if (!cmd_args[1])
	{
		while (tmp)
		{
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
	cmd_args++;
	while (*cmd_args)
	{
		if (validity_of_var_name(*cmd_args) < 0)
		{
			exit_status = -1;
		}
		else
		{
			// printf("dada");
			// printf("%d", validity_of_var_name())
			export_var(*cmd_args, our_env, validity_of_var_name(*cmd_args));
			// printf("here\n");
		}
		cmd_args++;
	}
	return (exit_status);
}