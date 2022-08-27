/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:17:45 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/22 08:59:49 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	skipper;
	int	sign;
	int	result;

	sign = 1;
	skipper = 0;
	result = 0;
	while (str[skipper] && ((str[skipper] >= 9 \
	&& str[skipper] <= 13) || str[skipper] == 32))
		skipper++;
	if (str[skipper] == '-' || str[skipper] == '+')
	{
		if (str[skipper] == '-')
			sign = -1;
		skipper++;
	}
	while (str[skipper] && ft_isdigit(str[skipper]))
	{
		result = result * 10 + str[skipper] - 48;
		skipper++;
	}
	return (result * sign);
}
