/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_client.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:24:49 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/07 18:01:42 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "../ft_printf/libft/libft.h"
#include "../headers/minitalk_client.h"
#include "../headers/error_handling.h"

int	*sent_bit(void)
{
	static int	bit;

	return (&bit);
}

void	acknowledgement(int signum, siginfo_t *siginfo, void *context)
{
	int	received;

	(void) context;
	(void) siginfo;
	received = (signum == SIGUSR2);
	if (received != *sent_bit())
		call_error("Incorrect bit received");
}

int	send_byte(int pid, char byte)
{
	int	i;
	int	ret;
	int	signal;
	struct sigaction	sig;

	i = 0b00000001;
	ret = 0;
	sig.sa_sigaction = acknowledgement;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sig, NULL) != 0)
		call_error("Sigaction sig1 error\n");
	if (sigaction(SIGUSR2, &sig, NULL) != 0)
		call_error("Sigaction sig2 error\n");
	while (i <= 0b10000000 && i > 0)
	{
		signal = SIGUSR1;
		if (byte & (char)i)
			signal = SIGUSR2;
		(*sent_bit()) = (signal == SIGUSR2);
		usleep(DELAY);
		ret += kill(pid, signal);
		pause();
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
