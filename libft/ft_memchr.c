/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:53:10 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/05 15:25:30 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptrs;

	ptrs = (unsigned char *)s;
	while (n)
	{
		if (*ptrs == (unsigned char)c)
			return (ptrs);
		ptrs++;
		n--;
	}
	return (NULL);
}
