/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 15:49:56 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/09 16:23:32 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
typedef struct s_signal_data
{
	int		pid;
	char	byte_progress;
	char	byte;
	char	*str;
}	t_signal_data;

#endif