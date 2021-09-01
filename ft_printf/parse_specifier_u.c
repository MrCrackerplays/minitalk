/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_specifier_u.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:43 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:55:44 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include "stdlib.h"

char	*parse_specifier_u(va_list *arg, t_conv *data)
{
	unsigned long long	input;
	int					count;
	char				*print;
	char				*precisioned;

	data->flags &= ~((1 << get_flag_value(' ')) | (1 << get_flag_value('+')));
	input = get_input(arg, data);
	count = get_ct(data, input, 10);
	print = create_width_print(data->field_width, ' ');
	if (print == NULL)
		return (NULL);
	precisioned = fill_ull_prcn(input, count, "0123456789");
	if (precisioned == NULL)
	{
		free(print);
		return (NULL);
	}
	put_prcn(print, precisioned, data, count);
	free(precisioned);
	return (print);
}
