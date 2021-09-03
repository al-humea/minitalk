/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:06:06 by al-humea          #+#    #+#             */
/*   Updated: 2021/09/03 15:21:37 by al-humea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	chrjoin(char **str, char c)
{
	int		i;
	char	*nstr;

	i = 0;
	if (*str == NULL)
		*str = ft_strdup("");
	if (c == 0)
		return ;
	nstr = malloc(ft_strlen(*str) + 2);
	if (!nstr)
		exit(EXIT_FAILURE);
	while ((*str)[i])
	{
		nstr[i] = (*str)[i];
		i++;
	}
	nstr[i] = c;
	i++;
	nstr[i] = '\0';
	free(*str);
	*str = NULL;
	*str = nstr;
	return ;
}
