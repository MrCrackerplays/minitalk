/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_specifier_i.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:02 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:55:02 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parse_specifier_i(va_list *arg, t_conv *data)
{
	data->specifier = 'd';
	return (parse_specifier_d(arg, data));
}
