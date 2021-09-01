/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:05:20 by al-humea          #+#    #+#             */
/*   Updated: 2021/09/01 11:46:45 by al-humea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"

static const char	*g_str;

/*
**SIMPLY CHECKS IF PID IS VALID
*/
int	is_pid(char *pid_str)
{
	int	i;
	int	pid;

	i = 0;
	pid = 0;
	if (!pid_str)
		return (-1);
	while (pid_str[i])
	{
		if (pid_str[i] < 48 || pid_str[i] > 57)
			return (-1);
		pid = (pid * 10) + pid_str[i] - 48;
		i++;
	}
	if (kill(pid, 0) < 0)
		return (-1);
	return (pid);
}

/*
**SENDS A LETTER BIT each time it is called
*/
void	send_bit(int *i, int *ci, int *c, int PID)
{
	if (*ci == 8)
	{
		*ci = 0;
		*i += 1;
		*c = g_str[*i];
	}
	if (*c & 0x01)
	{
		*c >>= 1;
		*ci += 1;
		kill(PID, SIGUSR1);
		return ;
	}
	*c >>= 1;
	*ci += 1;
	kill(PID, SIGUSR2);
	return ;
}

/*
**CLIENT HANDLES SIGNALS
**IF SIGUSR2 WAITS AND SENDS AN ACK REQUEST
**IF SIGUSR1 SENDS NEXT BIT (CI) FROM CHAR BYTE (g_str[I])
**C == CURRENT BYTE SAVE
*/
void	client(int sig, siginfo_t *siginfo, void *context)
{
	static int	i = 0;
	static int	ci = 0;
	static int	c = 0;

	(void)context;
	if (i == 0 && ci == 0)
		c = g_str[i];
	if (sig == SIGUSR2)
	{
		sleep(1);
		kill(siginfo->si_pid, SIGUSR1);
		return ;
	}
	if (sig == SIGUSR1)
	{
		if (ci == 8 && g_str[i] == 0)
		{
			ft_putstr_fd("Message received\n", 1);
			exit(EXIT_SUCCESS);
		}
		send_bit(&i, &ci, &c, siginfo->si_pid);
		return ;
	}
}

int	main(int ac, char **av)
{
	int					pid;
	struct sigaction	sa;

	pid = 0;
	if (ac > 1)
		pid = is_pid(av[1]);
	if (ac < 3 || pid < 0)
	{
		write(1, "Missing or invalid args\n", 24);
		exit (EXIT_FAILURE);
	}
	g_str = ft_strdup(av[2]);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = client;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	kill(pid, SIGUSR1);
	while (1)
	{
	}
}
