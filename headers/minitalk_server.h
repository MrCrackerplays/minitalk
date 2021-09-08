/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_server.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 15:49:56 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/08 17:49:31 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_SERVER_H
# define MINITALK_SERVER_H
# define DELAY 30
typedef struct s_signal_data
{
	int		client_pid;
	char	byte_progress;
	char	byte;
}	t_signal_data;

#endif