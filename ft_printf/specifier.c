/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specifier.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:55:58 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 17:27:03 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

static const char	*g_specifiers = "diuxXcsp%on";

int	get_specifier_index(char c)
{
	int	i;

	i = 0;
	while (g_specifiers[i] && g_specifiers[i] != c)
		i++;
	if (g_specifiers[i] == '\0')
		return (-1);
	return (i);
}

char	get_specifier(const char *str, int *position)
{
	char	character[2];

	character[0] = str[*position];
	character[1] = '\0';
	if (ft_strnstr(g_specifiers, &(character[0]), 50) == NULL)
		return ('\0');
	(*position)++;
	return (character[0]);
}
