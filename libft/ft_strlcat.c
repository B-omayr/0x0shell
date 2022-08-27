/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:40:51 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/11 11:22:20 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t dstsize)
{
	size_t	to_add;
	size_t	src_len;
	size_t	dst_len;
	size_t	j;

	j = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len + 1 > dstsize)
		return (dstsize + src_len);
	to_add = dstsize - dst_len - 1;
	while (j < to_add && src[j])
	{
		dst[dst_len + j] = (char)src[j];
		j++;
	}
	dst[dst_len + j] = 0;
	return (dst_len + src_len);
}
