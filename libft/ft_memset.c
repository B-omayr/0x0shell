/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:35:12 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/12 11:37:12 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*temp;

	if (!len)
		return (b);
	temp = b;
	i = 0;
	while (len)
	{
		temp[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
