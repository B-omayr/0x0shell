/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 18:07:57 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/02 17:10:41 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_message(char *value)
{
	printf("\e[7;91mMy_Minishell: syntax error near");
	printf(" unexpected token '%s'\e[0m\n", value);
}
