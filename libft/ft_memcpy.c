/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:57:44 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/05 15:51:33 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	int				i;

	if (dst == NULL && src == NULL)
		return (0);
	if (dst == src)
		return (dst);
	i = 0;
	pdest = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	while (n)
	{
		pdest[i] = psrc[i];
		i++;
		n--;
	}
	return (dst);
}
