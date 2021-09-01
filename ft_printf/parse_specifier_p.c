/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_specifier_p.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:28 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:55:28 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include "stdlib.h"

char	*fill_ull_precision(unsigned long long int input, int count, char *base)
{
	char	*precisioned;
	char	*itoa;
	int		len;

	precisioned = create_width_print(count, '0');
	if (precisioned == NULL)
		return (NULL);
	itoa = ft_ullitob(input, base);
	if (itoa == NULL)
	{
		free(precisioned);
		return (NULL);
	}
	len = ft_strlen(itoa);
	precisioned[1] = 'x';
	ft_memcpy(&(precisioned[count - len]), itoa, len * sizeof(char));
	free(itoa);
	return (precisioned);
}

int	get_p_count(t_conv *data, unsigned long long int input, int base_size)
{
	int			count;
	int			i;

	i = 1;
	while (input >= (unsigned long long)base_size)
	{
		input /= (unsigned long long)base_size;
		i++;
	}
	count = i + 2;
	if (data->field_width < count)
		data->field_width = count;
	return (count);
}

char	*parse_specifier_p(va_list *arg, t_conv *data)
{
	unsigned long long int	input;
	int						count;
	char					*print;
	char					*precisioned;

	input = va_arg(*arg, unsigned long long int);
	count = get_p_count(data, input, 16);
	print = create_width_print(data->field_width, ' ');
	if (print == NULL)
		return (NULL);
	precisioned = fill_ull_precision(input, count, "0123456789abcdef");
	if (precisioned == NULL)
	{
		free(print);
		return (NULL);
	}
	put_prcn(print, precisioned, data, count);
	free(precisioned);
	return (print);
}
