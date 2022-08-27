/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:53:58 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/26 09:57:08 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_there(char const *set, int c)
{	
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	len_s1;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len_s1 = ft_strlen(s1);
	while (s1[i] && is_there(set, s1[i]))
		i++;
	while (s1[i] && is_there(set, s1[len_s1 - 1]))
		len_s1--;
	return (ft_substr(s1, (unsigned int)i, len_s1 - i));
}
