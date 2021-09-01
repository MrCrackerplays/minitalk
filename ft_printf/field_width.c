/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   field_width.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:54:16 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:54:20 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include "stdlib.h"

int	get_field_width(const char *str, int *position, va_list *args)
{
	int	width;

	if (str[*position] == '*')
	{
		width = va_arg(*args, int);
		(*position)++;
	}
	else
	{
		width = ft_atoi(&(str[*position]));
		while (ft_isdigit(str[*position]))
			(*position)++;
	}
	return (width);
}

char	*create_width_print(int width, char fill)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * (width + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < width)
	{
		ret[i] = fill;
		i++;
	}
	ret[width] = '\0';
	return (ret);
}

int	count_u_digits(unsigned long long number, t_conv *data, int base_size,
	int prefix)
{
	int	i;

	i = 1;
	while (number >= (unsigned long long)base_size)
	{
		number /= (unsigned long long)base_size;
		i++;
	}
	if (data->precision == -1 && !is_flag_set(data->flags, '-')
		&& is_flag_set(data->flags, '0'))
		data->precision = data->field_width - prefix;
	if (i < data->precision)
		return (data->precision + prefix);
	return (i + prefix);
}

int	get_ct(t_conv *data, unsigned long long input, int base_size)
{
	int	count;
	int	prefix;

	prefix = 0;
	if (is_flag_set(data->flags, ' ') || is_flag_set(data->flags, '+'))
		prefix = 1;
	if ((data->specifier == 'x' || data->specifier == 'X')
		&& (is_flag_set(data->flags, '#')))
		prefix = 2;
	if (input == 0 && data->precision == 0)
		count = is_flag_set(data->flags, '+') || is_flag_set(data->flags, ' ');
	else
		count = count_u_digits(input, data, base_size, prefix);
	if (data->field_width < count)
		data->field_width = count;
	if ((data->precision == data->field_width)
		&& (is_flag_set(data->flags, ' ') || is_flag_set(data->flags, '+')))
		data->precision--;
	return (count);
}
