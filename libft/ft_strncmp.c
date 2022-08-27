/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:51:48 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/06 16:52:10 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	ptrs1 = (unsigned char *) s1;
	ptrs2 = (unsigned char *) s2;
	while (n && *ptrs1 && *ptrs2 && (*ptrs1 == *ptrs2))
	{
		ptrs1++;
		ptrs2++;
		n--;
	}
	if (!n || (!(*ptrs1) && !(*ptrs2)))
		return (0);
	return (*ptrs1 - *ptrs2);
}
