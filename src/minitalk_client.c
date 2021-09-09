/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_client.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:24:49 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/09 17:56:52 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "../ft_printf/libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../headers/minitalk.h"
#include "../headers/minitalk_client.h"

t_signal_data	*get_data_holder(void)
{
	static t_signal_data	data;

	return (&data);
}

void	print_exit_fd(const char *message, int exit_code, int fd)
{
	if (message != NULL)
		write(fd, message, ft_strlen(message));
	exit(exit_code);
}

void	send_bit(void)
{
	int	signal;

	if (get_data_holder()->byte_progress == 8)
	{
		if (get_data_holder()->byte == '\0')
			print_exit_fd("Client %i finished sending message!\n", 0, 0);
		get_data_holder()->byte = get_data_holder()->str[0];
		get_data_holder()->str++;
		get_data_holder()->byte_progress = 0;
	}
	signal = SIGUSR1;
	if (get_data_holder()->byte & (char)(0b00000001
		<< get_data_holder()->byte_progress))
		signal = SIGUSR2;
	usleep(DELAY);
	if (kill(get_data_holder()->pid, signal) < 0)
		print_exit_fd("Something went wrong trying to send data\n", 1, 2);
	usleep(DELAY);
	get_data_holder()->byte_progress++;
}

void	acknowledgement(int signum)
{
	if (signum == SIGUSR2)
		print_exit_fd("Server has shut down\n", 1, 2);
	send_bit();
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	get_data_holder()->pid = pid;
	get_data_holder()->str = argv[2];
	i = 0;
	ft_printf("Client %i started sending message!\n", getpid());
	signal(SIGUSR1, acknowledgement);
	signal(SIGUSR2, acknowledgement);
	get_data_holder()->byte = get_data_holder()->str[0];
	get_data_holder()->str++;
	send_bit();
	while (1)
		pause();
	return (0);
}
