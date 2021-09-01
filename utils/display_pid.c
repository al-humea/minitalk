/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:42:51 by al-humea          #+#    #+#             */
/*   Updated: 2021/09/01 11:46:58 by al-humea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	display_pid(void)
{
	char	*pid;

	pid = NULL;
	pid = ft_itoa(getpid());
	if (!pid)
	{
		ft_putstr_fd("Problem displaying PID\n", 1);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("PID =", 1);
	ft_putstr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	free(pid);
	pid = NULL;
}
