/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_client.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:24:49 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 17:56:30 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "../ft_printf/libft/libft.h"

int	main(int argc, char **argv)
{
	int	a;
	int	time;
	int ret;

	if (argc != 3)
		return (1);
	a = ft_atoi(argv[1]);
	time = 5;
	kill(a, SIGUSR1);
	// usleep(time);
	// kill(a, SIGUSR2);
	// usleep(time);
	// kill(a, SIGUSR2);
	// usleep(time);
	// kill(a, SIGUSR1);
	// usleep(time);
	// kill(a, SIGUSR2);
	// usleep(time);
	// kill(a, SIGUSR1);
	// usleep(time);
	// kill(a, SIGUSR1);
	usleep(time);
	kill(a, SIGUSR1);
	usleep(time);
	kill(a, SIGUSR2);
	usleep(time);
	ret = kill(a, SIGUSR1);
	ft_putnbr_fd(ret, 1);
}
