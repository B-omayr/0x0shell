/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:32:00 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/01 15:45:16 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_env_to_matrix(t_env *our_env)
{
	t_env 	*tmp;
	char	*tmp2;
	char	**matrix;
	int		size;

	tmp = our_env;
	size = 0;
	while (our_env)
	{
		size++;
		our_env = our_env->next;
	}
	matrix = (char **)ft_malloc(sizeof(char *) * (size + 1));
	if (!matrix)
		return (NULL);
	size = 0;
	while (tmp)
	{
		tmp2 = ft_strjoin(tmp->name, "=");
		matrix[size] = ft_strjoin(tmp2, tmp->value);
		//free(tmp2);
		size++;
		tmp = tmp->next;
	}
	matrix[size] = NULL;
	return (matrix);
}