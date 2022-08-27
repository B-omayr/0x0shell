/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:48:59 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/26 09:50:29 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*holder_char;

	holder_char = (char *)s;
	while (*holder_char != (char)c && *holder_char)
	{
		holder_char++;
	}
	if (*holder_char == (char)c)
		return (holder_char);
	return (NULL);
}
