/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:59:10 by youchenn          #+#    #+#             */
/*   Updated: 2022/08/30 18:44:22 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	cal_digit(int n)
{
	int	c;

	c = 0;
	while (n / 10)
	{
		c++;
		n = n / 10;
	}
	if (n >= -9 && n <= 9)
		c = c + 1;
	return (c);
}

static	char	*ft_str_rev(char *str)
{
	size_t	i;
	char	temp;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	if (!str)
		return (NULL);
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = temp;
		i++;
	}
	return (str);
}

static	char	*convert_to_string(char *nb_to_str, long nb, int sign)
{
	int	i;
	int	num_dig;

	i = 0;
	num_dig = cal_digit(nb);
	while (i < num_dig)
	{
		if (num_dig == 1)
		{
			nb_to_str[i] = nb + '0';
			break ;
		}
		nb_to_str[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	nb_to_str[num_dig + sign] = 0;
	return (nb_to_str);
}

char	*ft_itoa(int n)
{
	char	*nb_to_str;
	int		num_digit;
	long	nb;
	int		sign;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		nb *= -1;
	}
	num_digit = cal_digit(nb);
	nb_to_str = (char *)malloc(num_digit + sign + 1);
	if (!nb_to_str)
		return (NULL);
	if (n < 0)
		nb_to_str[num_digit] = '-';
	nb_to_str = convert_to_string(nb_to_str, nb, sign);
	return (ft_str_rev(nb_to_str));
}
