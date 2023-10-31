/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenezes <rmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:38:06 by rmenezes          #+#    #+#             */
/*   Updated: 2023/10/31 22:13:57 by rmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void	send_sig(int pid, unsigned char character)
{
	int	i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(420);
	}
}

void	catch_sig(int signal)
{
	if (signal == SIGUSR1)
		printf("Received bit 1\n");
	else if (signal == SIGUSR2)
		printf("Received bit 0\n");
}
// DONT FORGET TO SWTICH TO YOUR PRINTF DUMMY


int	main(int ac, char **av)
{
	__pid_t	server_pid;
	const char	*message;
	int	i;
	
	signal(SIGUSR1, catch_sig);
	signal(SIGUSR2, catch_sig);
	if (ac != 3)
	{
		printf("Wrong format, try this <pid>, <message>.\n If your message contains spaces, remember to use parentheses\n");
		exit(0);
	}
	server_pid = ft_atoi(av[1]);
	message = av[2];
	i = 0;
	while (message[i])
		send_sig(server_pid, message[i++]);
	send_sig(server_pid, '\0');
	return (0);
}