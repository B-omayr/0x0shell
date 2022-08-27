/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:17:48 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/26 09:56:43 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr_result;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ptr_result = (char *)malloc(len_s1 + len_s2 + 1);
	if (!ptr_result)
		return (NULL);
	ft_strlcpy(ptr_result, s1, len_s1 + 1);
	ft_strlcat(ptr_result, s2, len_s1 + len_s2 + 1);
	return (ptr_result);
}
