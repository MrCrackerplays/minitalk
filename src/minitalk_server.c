/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_server.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:11:42 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/11 15:35:51 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../ft_printf/libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../headers/minitalk.h"

t_signal_data	*get_data_holder(void)
{
	static t_signal_data	data;

	return (&data);
}

void	call_error(const char *message)
{
	if (message != NULL)
		write(2, message, ft_strlen(message));
	kill(get_data_holder()->pid, SIGUSR2);
	exit(1);
}

void	string_builder(void)
{
	char	*new_str;
	char	chr[2];

	chr[1] = '\0';
	chr[0] = get_data_holder()->byte;
	new_str = ft_strjoin(get_data_holder()->str, &chr[0]);
	free(get_data_holder()->str);
	if (new_str == NULL)
		call_error("Strjoin fail\n");
	get_data_holder()->str = new_str;
	get_data_holder()->byte_progress = 0;
	if (chr[0] == '\0')
	{
		ft_printf("[client %i]>%s\n", get_data_holder()->pid,
			get_data_holder()->str);
		free(get_data_holder()->str);
		get_data_holder()->str = ft_calloc(1, sizeof(char));
		if (get_data_holder()->str == NULL)
			call_error("Malloc fail\n");
		get_data_holder()->pid = 0;
	}
}

void	bit_from_signal(int signum, siginfo_t *siginfo, void *context)
{
	int	pid;

	(void) context;
	if (get_data_holder()->pid == 0)
		get_data_holder()->pid = siginfo->si_pid;
	pid = get_data_holder()->pid;
	if (signum == SIGUSR1)
		get_data_holder()->byte = get_data_holder()->byte
		& ~(1 << get_data_holder()->byte_progress);
	else if (signum == SIGUSR2)
		get_data_holder()->byte = get_data_holder()->byte
		| 1 << get_data_holder()->byte_progress;
	(get_data_holder()->byte_progress)++;
	if (get_data_holder()->byte_progress == 8)
		string_builder();
	if (kill(pid, SIGUSR1) != 0)
		call_error("Something went wrong trying to send data\n");
}

int	main(void)
{
	struct sigaction	sig;

	ft_printf("PID:%i\n", getpid());
	get_data_holder()->str = ft_calloc(1, sizeof(char));
	if (get_data_holder()->str == NULL)
		call_error("Malloc fail\n");
	sig.sa_sigaction = bit_from_signal;
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, NULL) != 0)
		call_error("Sigaction sig1 error\n");
	if (sigaction(SIGUSR2, &sig, NULL) != 0)
		call_error("Sigaction sig2 error\n");
	while (1)
		pause();
}
