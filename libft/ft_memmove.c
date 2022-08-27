/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:08:26 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/13 11:56:27 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	size_t			i;

	if (dst == src)
		return (dst);
	pdest = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	i = 0;
	if (psrc > pdest)
	{
		while (i < len)
		{
			pdest[i] = psrc[i];
			i++;
		}
		return (dst);
	}
	else
	{
		while (len--)
			pdest[len] = psrc[len];
		return (dst);
	}
}
