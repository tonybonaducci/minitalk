/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenezes <rmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:55:12 by rmenezes          #+#    #+#             */
/*   Updated: 2023/10/31 21:28:40 by rmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>



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
		usleep(42);
	}
}

int	main(int ac, char **av)
{
	int						i;
	__pid_t			server_pid;
	const char		*message;

	if (ac != 3)
	{
		printf("Usage: %s <pid> <message> \n", av[0]);
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