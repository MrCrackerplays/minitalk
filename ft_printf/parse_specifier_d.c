/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_specifier_d.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:54:57 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:54:57 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include "stdlib.h"

char	*fill_precision(long long input, int count, t_conv *data, char *base)
{
	char	*precisioned;
	char	*itoa;
	int		len;

	precisioned = create_width_print(count, '0');
	if (precisioned == NULL)
		return (NULL);
	if (input < 0)
		itoa = ft_ullitob(-((unsigned long long)input), base);
	else
		itoa = ft_ullitob((unsigned long long)input, base);
	if (itoa == NULL)
		free(precisioned);
	if (itoa == NULL)
		return (NULL);
	len = ft_strlen(itoa);
	ft_memcpy(&(precisioned[count - len]), itoa, len * sizeof(char));
	free(itoa);
	if (input < 0)
		precisioned[0] = '-';
	else if (is_flag_set(data->flags, '+'))
		precisioned[0] = '+';
	else if (is_flag_set(data->flags, ' '))
		precisioned[0] = ' ';
	return (precisioned);
}

int	count_digits(long int number, t_conv *data, int base_size, int prefix)
{
	int	i;

	i = 1;
	if (number > 0)
		number = -number;
	while (number <= -base_size)
	{
		number /= base_size;
		i++;
	}
	if (data->precision == -1 && !is_flag_set(data->flags, '-')
		&& is_flag_set(data->flags, '0'))
		data->precision = data->field_width - prefix;
	if (i < data->precision)
		return (data->precision + prefix);
	return (i + prefix);
}

int	get_count(t_conv *data, long long input, int base_size)
{
	int	count;
	int	prefix;

	prefix = 0;
	if (input < 0 || is_flag_set(data->flags, ' ')
		|| is_flag_set(data->flags, '+'))
		prefix = 1;
	if ((data->specifier == 'x' || data->specifier == 'X')
		&& (is_flag_set(data->flags, '#')))
		prefix = 2;
	if (input == 0 && data->precision == 0)
		count = is_flag_set(data->flags, '+') || is_flag_set(data->flags, ' ');
	else
		count = count_digits(input, data, base_size, prefix);
	if (data->field_width < count)
		data->field_width = count;
	if ((data->precision == data->field_width) && (input < 0
			|| is_flag_set(data->flags, ' ') || is_flag_set(data->flags, '+')))
		data->precision--;
	return (count);
}

char	*parse_specifier_d(va_list *arg, t_conv *data)
{
	long long	input;
	int			count;
	char		*print;
	char		*precisioned;

	input = get_input(arg, data);
	count = get_count(data, input, 10);
	print = create_width_print(data->field_width, ' ');
	if (print == NULL)
		return (NULL);
	precisioned = fill_precision(input, count, data, "0123456789");
	if (precisioned == NULL)
	{
		free(print);
		return (NULL);
	}
	put_prcn(print, precisioned, data, count);
	free(precisioned);
	return (print);
}
