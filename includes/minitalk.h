/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 11:20:47 by al-humea          #+#    #+#             */
/*   Updated: 2021/09/07 19:57:54 by al-humea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

//UTILS
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int nbr);
void	display_pid(void);
void	chrjoin(char **s, char c);
//server
int		acknowledge(int *cpid, siginfo_t *siginfo);
void	print(int *c, int *ci, char **s, int *cpid);
void	makechar(int sig, siginfo_t *siginfo, void *context);
//client
int		is_pid(char *pid_str);
void	send_bit(int *i, int *ci, int *c, int PID);
void	client(int sig, siginfo_t *siginfo, void *context);

#endif