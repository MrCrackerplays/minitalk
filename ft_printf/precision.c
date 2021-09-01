/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:53 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:55:54 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include "stdlib.h"

int	get_precision(const char *str, int *position, va_list *args)
{
	int	precision;

	if (str[*position] != '.')
		return (-1);
	(*position)++;
	precision = 0;
	if (str[*position] == '*')
	{
		precision = va_arg(*args, int);
		if (precision < 0)
			precision = -1;
		(*position)++;
	}
	else if (ft_isdigit(str[*position]))
	{
		precision = ft_atoi(&(str[*position]));
		while (ft_isdigit(str[*position]))
			(*position)++;
	}
	return (precision);
}

char	*fill_ull_prcn(unsigned long long input, int count, char *base)
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
	ft_memcpy(&(precisioned[count - len]), itoa, len * sizeof(char));
	free(itoa);
	return (precisioned);
}

void	put_prcn(char *print, char *prcsion, t_conv *data, int count)
{
	if ((data->specifier == 'x' || data->specifier == 'X')
		&& is_flag_set(data->flags, '#'))
		prcsion[1] = data->specifier;
	if (is_flag_set(data->flags, '-'))
		ft_memmove(print, prcsion, count * sizeof(char));
	else
		ft_memmove(&(print[ft_strlen(print) - count]), prcsion, count
			* sizeof(char));
}
