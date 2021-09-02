/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_client.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:24:49 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/02 14:33:47 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "../ft_printf/libft/libft.h"
#include "../headers/minitalk_client.h"

int	send_byte(int pid, char byte)
{
	int	i;
	int	ret;

	i = 0b00000001;
	ret = 0;
	while (i <= 0b10000000 && i > 0)
	{
		if (byte & (char)i)
			ret += kill(pid, SIGUSR2);
		else
			ret += kill(pid, SIGUSR1);
		usleep(DELAY);
		i <<= 1;
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;
	int	ret;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i] != '\0')
	{
		ret = send_byte(pid, argv[2][i]);
		if (ret < 0)
		{
			write(2, "Something went wrong trying to send data\n", 42);
			return (1);
		}
		i++;
	}
	ret = send_byte(pid, argv[2][i]);
	if (ret < 0)
	{
		write(2, "Something went wrong trying to finish sending data\n", 52);
		return (1);
	}
	return (0);
}
