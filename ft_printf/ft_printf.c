/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:54:28 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:54:29 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "unistd.h"
#include "libft/libft.h"
#include "stdlib.h"

int	print_raw(const char *str, int position, int start)
{
	int	amount;

	amount = position - start;
	write(1, &(str[start]), amount);
	return (amount);
}

t_conv	*prep_conv(va_list *arg, t_conv *data, const char *str, int *pos)
{
	data->flags = get_flags(str, pos);
	data->field_width = get_field_width(str, pos, arg);
	if (data->field_width < 0)
	{
		data->field_width *= -1;
		data->flags |= 1 << get_flag_value('-');
	}
	data->precision = get_precision(str, pos, arg);
	data->length_mod = get_length_mod(str, pos);
	data->specifier = get_specifier(str, pos);
	return (data);
}

int	prnt_conv(va_list *arg, t_conv *data)
{
	static	char*(*parse[])(va_list *, t_conv *) = {parse_specifier_d,
			parse_specifier_i, parse_specifier_u, parse_specifier_x,
			parse_specifier_X, parse_specifier_c, parse_specifier_s,
			parse_specifier_p, parse_specifier_percent, parse_specifier_o,
			parse_specifier_n};
	char		*print;
	int			i;

	i = get_specifier_index(data->specifier);
	if (i < 0)
		return (-1);
	print = parse[i](arg, data);
	if (print == NULL)
		return (-1);
	write(1, print, data->field_width);
	free(print);
	return (data->field_width);
}

int	step_through(const char *str, t_conv *data, va_list *args)
{
	int	position;
	int	start;
	int	amount;

	position = 0;
	data->read = 0;
	while (str[position] != '\0')
	{
		start = position;
		while (str[position] != '%' && str[position] != '\0')
			position++;
		data->read += print_raw(str, position, start);
		if (str[position] == '\0')
			break ;
		position++;
		prep_conv(args, data, str, &position);
		amount = prnt_conv(args, data);
		if (amount == -1)
			return (-1);
		data->read += amount;
	}
	return (data->read);
}

int	ft_printf(const char *str, ...)
{
	t_conv	*data;
	va_list	args;
	int		len;

	data = ft_calloc(1, sizeof(*data));
	if (data == NULL)
		return (-1);
	va_start(args, str);
	len = step_through(str, data, &args);
	va_end(args);
	free(data);
	return (len);
}
