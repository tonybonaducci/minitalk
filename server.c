/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenezes <rmenezes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:53:35 by rmenezes          #+#    #+#             */
/*   Updated: 2023/10/31 21:29:25 by rmenezes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_signal(int signal)
{
	static unsigned char	current_char;
	static int				bit_i;
	
	current_char |= (signal == SIGUSR1);
	bit_i++;
	if (bit_i == 8)
	{
		if (current_char == '\0')
			printf("\n");
		else
			printf("%c", current_char);
		bit_i = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;	
}

int	main(void)
{
	printf("%d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);	
}