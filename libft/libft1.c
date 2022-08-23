/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:32:51 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/23 13:49:09 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strcmp(char *str, char *ptr)
{
    int i;

    i = 0;
    while (str[i] && ptr[i] && str[i] == ptr[i])
        i++;
    return (str[i] - ptr[i]);
}

char **ft_split(char *env)
{
	char **str;
    int i;
    
    i = 0;
    str = malloc(sizeof(char **) * 2);
    str[0]= malloc(sizeof(char) * get_lenght(env, '=') + 1);
    str[1] = malloc(sizeof(char) * get_lenght(env, '\0') + 1);
    while(env[i] != '=')
    {
        str[0][i] = env[i];
        i++;
    }
    str[0][i] = '\0';
    str[1] = get_s1(env, str, i);
	return (str);
}

int alpha_numeric(char c)
{
	if (!c)
		return (0);
	if ((c >= 0 && c <= 9) || (c >= 'a' && c <= 'z') 
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int get_lenght(char *ln, char c)
{
    int i;

    i = 0;
	if (ln == NULL)
		return (0);
    while (ln[i] != c)
        i++;
    return (i);
}

char *ft_strdup(char *str)
{
	char *ptr;
	int len;
	int i;

	i = -1;
	len = get_lenght(str, '\0');
	ptr = malloc(sizeof(char) * len + 1);
	while (str[++i] != '\0')
		ptr[i] = str[i];
    ptr[i] = '\0';
    return (ptr);
}

char *ft_strchr(char *str, char c)
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
	while (ln[i] != '\0' && (ft_strchr("|> <;", ln[i])) == NULL)
	{
		i++;
		len++;
	}
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
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