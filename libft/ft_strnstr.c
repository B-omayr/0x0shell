/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:37:05 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/12 11:57:30 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *searched_str, size_t len)
{
	char	*pstr;
	char	*psearched_str;
	size_t	i;
	size_t	j;

	pstr = (char *)str;
	psearched_str = (char *)searched_str;
	i = 0;
	if (psearched_str[i] == 0)
		return (pstr);
	while (i <= len && pstr[i])
	{
		j = 0;
		if (pstr[i] == psearched_str[j])
		{
			while ((pstr[i + j] == psearched_str[j]) && psearched_str[j])
				j++;
			if (!psearched_str[j] && i + j <= len)
				return (&pstr[i]);
		}
		i++;
	}
	return (NULL);
}
