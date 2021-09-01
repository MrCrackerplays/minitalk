/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_server.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:11:42 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 17:44:08 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "../ft_printf/libft/libft.h"
#include "../ft_printf/ft_printf.h"

void	zero(int signum)
{
	ft_printf("zero%i\n", signum);
}

void	one(int signum)
{
	ft_printf("one%i\n", signum);
}

int	main(void)
{
	int		pid;
	char	*str;
	int		count;

	pid = getpid();
	str = NULL;
	count = 0;
	ft_printf("PID:%i\n", pid);
	signal(SIGUSR1, zero);
	signal(SIGUSR2, one);
	while (count < 10)
	{
		pause();
		ft_putstr_fd("pause\n", 1);
		count++;
	}
	if (str)
		ft_printf("%s", str);
	ft_putstr_fd("eindserver\n", 1);
}
