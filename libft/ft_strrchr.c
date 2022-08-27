/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:49:59 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/06 16:09:06 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*holder_char;
	size_t	len;

	holder_char = (char *)s;
	len = ft_strlen(holder_char);
	while (len && *holder_char && holder_char[len] != (char) c)
		len--;
	if (holder_char[len] == (char)c)
		return (&holder_char[len]);
	return (NULL);
}
