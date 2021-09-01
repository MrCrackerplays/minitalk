/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:54:23 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 17:26:39 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

static const char	*g_flags = "-0 +#";

int	get_flag_value(char c)
{
	int	i;

	i = 0;
	while (g_flags[i] && g_flags[i] != c)
		i++;
	if (g_flags[i] == '\0')
		return (-1);
	return (i);
}

int	get_flags(const char *str, int *position)
{
	int		flags;
	char	character[2];

	flags = 0;
	character[1] = '\0';
	character[0] = str[*position];
	while (ft_strnstr(g_flags, &character[0], 50))
	{
		flags |= 1 << get_flag_value(character[0]);
		(*position)++;
		character[0] = str[*position];
	}
	return (flags);
}

int	is_flag_set(int flag, char c)
{
	int	bit;

	bit = get_flag_value(c);
	if (bit == -1)
		return (0);
	bit = (flag >> bit) & 1;
	return (bit);
}
