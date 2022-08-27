/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:11:11 by youchenn          #+#    #+#             */
/*   Updated: 2021/11/26 09:58:29 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static	int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] && str[i] != c && (str[i + 1] == c || !str[i + 1]))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static	size_t	last_index(const char *str, char c)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] != c && str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static	char	**free_tab(char **tab)
{
	int	j;

	j = -1;
	if (!tab)
		return (NULL);
	while (tab[++j])
		free(tab[j]);
	free(tab);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	int				j;

	i = -1;
	j = 0;
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			tab[j] = ft_substr(s, i, last_index(&s[i], c));
			if (!tab[j])
				return (free_tab(tab));
			i = i + last_index(&s[i], c) - 1;
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
