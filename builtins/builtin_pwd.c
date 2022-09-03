/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:23:19 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/03 14:51:10 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_pwd(void)
{
	if (!getcwd(0, 0))
	{
		printf("%s\n", getenv("PWD"));
		return ;
	}
	printf("%s\n", getcwd(NULL, 0));
}