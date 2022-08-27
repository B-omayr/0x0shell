/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:04:25 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/12 11:59:15 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptrs;
	size_t	len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ptrs = (char *)malloc(len + 1);
	if (!ptrs)
		return (NULL);
	while (i < len)
	{
		ptrs[i] = f(i, s[i]);
		i++;
	}
	ptrs[i] = 0;
	return (ptrs);
}
