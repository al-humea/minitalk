/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:26:14 by al-humea          #+#    #+#             */
/*   Updated: 2021/09/07 22:01:47 by al-humea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"

int	acknowledge(int *cpid, siginfo_t *siginfo)
{
	if (*cpid == 0)
	{
		*cpid = siginfo->si_pid;
		kill(*cpid, SIGUSR1);
		return (0);
	}
	if (siginfo->si_pid != *cpid)
	{
		kill(siginfo->si_pid, SIGUSR2);
		return (0);
	}
	return (1);
}

void	print(int *c, int *ci, char **s, int *cpid)
{
	chrjoin(s, *c);
	if (*c == 0)
	{
		kill(*cpid, SIGUSR1);
		ft_putstr_fd(*s, 1);
		ft_putchar_fd('\n', 1);
		free(*s);
		*s = NULL;
		*cpid = 0;
		*c = 0;
		*ci = 0;
		return ;
	}
	*c = 0;
	*ci = 0;
	kill(*cpid, SIGUSR1);
}

/*
**SIGNAL HANDLER
**CREATES A CHAR FROM THE BITS OF A REVERSED BYTE AND ADDS IT TO AN STR
**
**IF SIGUSR1
**	IF !ACK
**		RETURN
**	ADD A BIT TO CHAR BYTE + RIGHT SHIFT
**IF SIGUSR2
**	RIGHT SHIFT CHAR_BYTE
**IF BYTE FULL
**	ADD TO STR
**	IF BYTE == 0
**		PRINT
**
*/
void	makechar(int sig, siginfo_t *siginfo,
							__attribute__((unused))void *context)
{
	static int	cpid = 0;
	static char	*s = NULL;
	static int	c = 0x80;
	static int	ci = 0;

	if (sig == SIGUSR1)
	{
		if (!acknowledge(&cpid, siginfo))
			return ;
		c >>= 1;
		c += 0x80;
	}
	if (sig == SIGUSR2)
		c >>= 1;
	ci++;
	if (ci == 8)
	{
		print(&c, &ci, &s, &cpid);
		return ;
	}
	kill(cpid, SIGUSR1);
}

void	kill_handler(__attribute__((unused))int signum)
{
	ft_putstr_fd("\nServer stopped.\n", 1);
	exit(EXIT_SUCCESS);
}

int	main(void)
{
	struct sigaction	sa;
	struct sigaction	sk;

	display_pid();
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = makechar;
	sk.sa_handler = kill_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sk, NULL);
	sigaction(SIGQUIT, &sk, NULL);
	while (1)
		sleep(42);
}
