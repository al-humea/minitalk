/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:26:14 by al-humea          #+#    #+#             */
/*   Updated: 2021/09/01 11:46:55 by al-humea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"

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
void	makechar(int sig, siginfo_t *siginfo, void *context)
{
	static int	cpid = 0;
	static char	*s = NULL;
	static int	c = 0x80;
	static int	ci = 0;

	(void)context;
	if (sig == SIGUSR1)
	{
		if (!acknowledge(&cpid, siginfo))
			return ;
		c >>= 1;
		c += 0x80;
		ci++;
	}
	if (sig == SIGUSR2)
	{
		c >>= 1;
		ci++;
	}
	if (ci == 8)
	{
		print(&c, &ci, &s, &cpid);
		return ;
	}
	kill(cpid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	display_pid();
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = makechar;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
}
