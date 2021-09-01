/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itob.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:54:40 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 14:54:41 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include "stdlib.h"

char	*insert_base(size_t count, unsigned long int n, size_t size, char *base)
{
	size_t	i;
	char	*converted;

	i = 0;
	converted = malloc(sizeof(char) * (count + 1));
	if (converted == NULL)
		return (NULL);
	converted[count] = '\0';
	while (i < count)
	{
		converted[count - 1 - i] = base[n % size];
		n /= size;
		i++;
	}
	return (converted);
}

char	*ft_ullitob(unsigned long int n, char *base)
{
	size_t	base_size;
	size_t	count;
	size_t	i;

	base_size = ft_strlen(base);
	if (base == NULL || base_size < 2)
		return (NULL);
	count = 1;
	i = n;
	while (i >= base_size)
	{
		i /= base_size;
		count++;
	}
	return (insert_base(count, n, base_size, base));
}
