/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 11:53:55 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/07 12:48:46 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../ft_printf/libft/libft.h"
#include "../headers/error_handling.h"

void	call_error(const char *message)
{
	if (message != NULL)
		write(2, message, ft_strlen(message));
	exit(1);
}
