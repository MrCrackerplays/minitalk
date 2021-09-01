/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   length_modifier.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:54:46 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 17:26:57 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

static const char	*g_length_mods = "hlhhll";

t_length_mod	get_length_mod(const char *str, int *position)
{
	t_length_mod	mod;
	char			*ch;
	char			holder[2];

	holder[0] = str[*position];
	holder[1] = '\0';
	ch = ft_strnstr(g_length_mods, &(holder[0]), 50);
	if (!ch)
		return (none);
	(*position)++;
	if (*ch == str[*position] && (str - 1) != ft_strrchr(g_length_mods, *ch))
	{
		(*position)++;
		if (*ch == 'h')
			return (hh);
		return (ll);
	}
	mod = (t_length_mod)(1 + ch - g_length_mods);
	return (mod);
}

long long	get_input(va_list *arg, t_conv *data)
{
	if (data->specifier == 'i' || data->specifier == 'd')
	{
		if (data->length_mod == h)
			return ((short)va_arg(*arg, int));
		if (data->length_mod == hh)
			return ((char)va_arg(*arg, int));
		if (data->length_mod == l)
			return ((long)va_arg(*arg, long));
		if (data->length_mod == ll)
			return ((long long)va_arg(*arg, long long));
		return (va_arg(*arg, int));
	}
	if (data->length_mod == h)
		return ((unsigned short)va_arg(*arg, unsigned int));
	if (data->length_mod == hh)
		return ((unsigned char)va_arg(*arg, unsigned int));
	if (data->length_mod == l)
		return ((unsigned long)va_arg(*arg, unsigned long));
	if (data->length_mod == ll)
		return ((unsigned long long)va_arg(*arg, unsigned long long));
	return (va_arg(*arg, unsigned int));
}
