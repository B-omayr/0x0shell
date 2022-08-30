/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 09:34:00 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/29 15:50:51 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char *ft_strchr1(char *str, char c)
{
    int i;
    int len;

    i = 0;
    len = get_lenght(str, '\0');
    if (c == '\0')
        return (&str[len]);
    while (str[i])
    {
        if (str[i] == c)
            return (&str[i]);
        i++;
    }
    return (NULL);
}

int	lenght_of_word(char *ln, int *index)
{
	int i;
	int len;

	i = *index;
	len = 0;
	while (ln[i] != '\0' && (ft_strchr1("|> <;", ln[i])) == NULL)
	{
		i++;
		len++;
	}
	return (len);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (!s1)
		s1 = ft_strdup1("");
	if (!s2)
		s2 = ft_strdup1("");
	len = get_lenght(s1, '\0') + get_lenght(s2, '\0') + 1;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s1[i])
		str[r++] = s1[i++];
	i = 0;
	while (s2[i])
		str[r++] = s2[i++];
	str[r] = 0;
    free(s1);
	return (str);
}

int check_quotess(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}