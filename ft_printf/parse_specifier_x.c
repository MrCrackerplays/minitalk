/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_specifier_x.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:49 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:55:50 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include "stdlib.h"

char	*parse_specifier_x(va_list *arg, t_conv *data)
{
	unsigned long long	input;
	int					count;
	char				*base;
	char				*print;
	char				*precisioned;

	data->flags &= ~((1 << get_flag_value(' ')) | (1 << get_flag_value('+')));
	base = "0123456789abcdef";
	if (data->specifier == 'X')
		base = "0123456789ABCDEF";
	input = get_input(arg, data);
	if (input == 0)
		data->flags &= ~(1 << get_flag_value('#'));
	count = get_ct(data, input, 16);
	print = create_width_print(data->field_width, ' ');
	if (print == NULL)
		return (NULL);
	precisioned = fill_ull_prcn(input, count, base);
	if (precisioned == NULL)
		free(print);
	if (precisioned == NULL)
		return (NULL);
	put_prcn(print, precisioned, data, count);
	free(precisioned);
	return (print);
}

char	*parse_specifier_X(va_list *arg, t_conv *data)
{
	if (data->specifier != 'X')
		return (NULL);
	return (parse_specifier_x(arg, data));
}
