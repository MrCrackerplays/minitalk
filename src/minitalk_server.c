/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_server.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:11:42 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/08 17:49:57 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../ft_printf/libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../headers/error_handling.h"
#include "../headers/minitalk_server.h"

t_signal_data	*get_data_holder(void)
{
	static t_signal_data	data;

	return (&data);
}

void	bit_from_signal(int signum, siginfo_t *siginfo, void *context)
{
	(void) context;
	get_data_holder()->client_pid = siginfo->si_pid;
	if (signum == SIGUSR1)
		get_data_holder()->byte = get_data_holder()->byte
		& ~(1 << get_data_holder()->byte_progress);
	else if (signum == SIGUSR2)
		get_data_holder()->byte = get_data_holder()->byte
		| 1 << get_data_holder()->byte_progress;
	(get_data_holder()->byte_progress)++;
}

int	main(void)
{
	char				*str;
	char				*temp;
	char				chr[2];
	int					count;
	struct sigaction	sig;

	str = ft_calloc(1, sizeof(char));
	if (str == NULL)
		call_error("Malloc fail\n");
	chr[1] = '\0';
	chr[0] = '~';
	count = 0;
	ft_printf("PID:%i\n", getpid());
	sig.sa_sigaction = bit_from_signal;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sig, NULL) != 0)
		call_error("Sigaction sig1 error\n");
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	if (sigaction(SIGUSR2, &sig, NULL) != 0)
		call_error("Sigaction sig2 error\n");
	while (1)
	{
		if (count != 0)
		{
			usleep(DELAY);
			if ((get_data_holder()->byte & 1 << (get_data_holder()->byte_progress - 1)) != 0)
				kill(get_data_holder()->client_pid, SIGUSR2);
			else
				kill(get_data_holder()->client_pid, SIGUSR1);
		}
		pause();
		usleep(DELAY);
		count++;
		if (count % 8 == 0)
		{
			chr[0] = get_data_holder()->byte;
			temp = ft_strjoin(str, &chr[0]);
			if (str != NULL)
				free(str);
			if (temp == NULL)
				call_error("Strjoin fail\n");
			str = temp;
			get_data_holder()->byte = 0;
			get_data_holder()->byte_progress = 0;
		}
		if (str != NULL && chr[0] == '\0')
		{
			ft_printf("[client %i]>%s\n", get_data_holder()->client_pid, str);
			free(str);
			str = ft_calloc(1, sizeof(char));
			if (str == NULL)
				call_error("Malloc fail\n");
			chr[0] = '~';
			count = 0;
			if ((get_data_holder()->byte & 1 << (get_data_holder()->byte_progress - 1)) != 0)
				kill(get_data_holder()->client_pid, SIGUSR2);
			else
				kill(get_data_holder()->client_pid, SIGUSR1);
		}
	}
}
