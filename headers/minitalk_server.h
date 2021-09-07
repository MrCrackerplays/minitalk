/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk_server.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 15:49:56 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/07 16:51:24 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_SERVER_H
# define MINITALK_SERVER_H
typedef struct s_signal_data
{
	int		client_pid;
	char	byte_progress;
	char	byte;
}	t_signal_data;

#endif