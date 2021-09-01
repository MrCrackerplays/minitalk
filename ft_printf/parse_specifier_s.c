/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_specifier_s.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:40 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:55:40 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

char	*parse_specifier_s(va_list *arg, t_conv *data)
{
	char	*input;
	char	*print;
	int		length;

	input = va_arg(*arg, char *);
	if (input == NULL)
		input = "(null)";
	length = ft_strlen(input);
	if (data-> precision != -1 && data->precision < length)
		length = data->precision;
	if (length > data->field_width)
		data->field_width = length;
	print = create_width_print(data->field_width, ' ');
	if (print == NULL)
		return (NULL);
	put_prcn(print, input, data, length);
	return (print);
}
