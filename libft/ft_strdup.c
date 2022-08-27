/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:16:52 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/26 09:55:17 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ps1;
	int		i;

	i = 0;
	ps1 = (char *)malloc(ft_strlen(s1) + 1);
	if (!ps1)
		return (NULL);
	while (s1[i])
	{
		ps1[i] = s1[i];
		i++;
	}
	ps1[i] = '\0';
	return (ps1);
}
