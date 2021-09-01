/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_specifier_percent.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:35 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 17:27:47 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stddef.h"
#include "stdlib.h"

char	*parse_specifier_percent(va_list *arg, t_conv *data)
{
	char	*print;

	if (arg)
	{
		;
	}
	print = malloc(sizeof(char) * 2);
	if (print == NULL)
		return (NULL);
	print[0] = '%';
	print[1] = '\0';
	data->field_width = 1;
	return (print);
}
