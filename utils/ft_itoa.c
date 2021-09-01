/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 20:32:31 by al-humea          #+#    #+#             */
/*   Updated: 2021/09/01 11:47:01 by al-humea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	nbtoright(char *str, int m)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	str[i + 1] = '\0';
	while (i > m)
	{
		str[i] = str[i - 1];
		i--;
	}
	str[i] = 0;
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		m;
	long	nb;

	nb = nbr;
	m = 0;
	str = malloc(12);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[m] = '-';
		nb *= -1;
		m++;
	}
	str[m] = '\0';
	while (nb > 9)
	{
		nbtoright(str, m);
		str[m] = (nb % 10) + 48;
		nb /= 10;
	}
	nbtoright(str, m);
	str[m] = nb + 48;
	return (str);
}
