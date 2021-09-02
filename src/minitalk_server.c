/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_server.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 13:11:42 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/02 17:55:20 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "../ft_printf/libft/libft.h"
#include "../ft_printf/ft_printf.h"

int	*get_byte(void)
{
	static int	value;

	return (&value);
}

int	*bit_count(void)
{
	static int	count;

	return (&count);
}

void	bit_from_signal(int signum)
{
	if (signum == SIGUSR1)
		(*get_byte()) = *get_byte() & ~(1 << *bit_count());
	else if (signum == SIGUSR2)
		(*get_byte()) = *get_byte() | 1 << *bit_count();
	(*bit_count())++;
}

int	main(void)
{
	int		pid;
	char	*str;
	char	*temp;
	char	chr[2];
	int		count;

	pid = getpid();
	str = malloc(sizeof(char));
	*str = '\0';
	chr[1] = '\0';
	chr[0] = '~';
	count = 0;
	ft_printf("PID:%i\n", pid);
	signal(SIGUSR1, bit_from_signal);
	signal(SIGUSR2, bit_from_signal);
	while (1)
	{
		pause();
		count++;
		if (count % 8 == 0)
		{
			chr[0] = (char)(*get_byte());
			// ft_printf("\n8deel:'%c'", chr[0]);
			temp = ft_strjoin(str, &chr[0]);
			if (str != NULL)
				free(str);
			if (temp == NULL)
			{
				write(2, "strjoin fail\n", 14);
				exit(1);
			}
			str = temp;
			*get_byte() = 0;
			*bit_count() = 0;
		}
		if (str != NULL && chr[0] == '\0')
		{
			ft_printf("[client]>%s\n", str);
			free(str);
			str = malloc(sizeof(char));
			*str = '\0';
			chr[0] = '~';
		}
	}
}
