/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdruart <pdruart@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/01 14:54:34 by pdruart       #+#    #+#                 */
/*   Updated: 2021/09/01 17:24:49 by pdruart       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
/* Includes */
# include "stdarg.h"

/* Typedef Structures */
typedef enum e_length_mod
{
	none = 0,
	h,
	l,
	hh,
	ll
}	t_length_mod;
typedef struct s_conv
{
	int				flags;
	int				field_width;
	int				precision;
	t_length_mod	length_mod;
	char			specifier;
	int				read;
}	t_conv;
/* Function Definitions */
int				ft_printf(const char *s, ...);
int				get_flags(const char *str, int *position);
int				get_field_width(const char *str, int *position, va_list *args);
int				get_precision(const char *str, int *position, va_list *args);
char			get_specifier(const char *str, int *position);
t_length_mod	get_length_mod(const char *str, int *position);
int				get_flag_value(char c);
long long		get_input(va_list *arg, t_conv *data);
/* Utility Functions */
int				is_flag_set(int flag, char c);
int				get_specifier_index(char c);
char			*create_width_print(int width, char fill);
char			*ft_ullitob(unsigned long int n, char *base);
int				get_ct(t_conv *data, unsigned long long input, int base_size);
void			put_prcn(char *print, char *prcn, t_conv *data, int count);
char			*fill_ull_prcn(unsigned long long input, int count, char *base);
/* Specifier Parsers */
char			*parse_specifier_c(va_list *arg, t_conv *data);
char			*parse_specifier_d(va_list *arg, t_conv *data);
char			*parse_specifier_i(va_list *arg, t_conv *data);
char			*parse_specifier_p(va_list *arg, t_conv *data);
char			*parse_specifier_s(va_list *arg, t_conv *data);
char			*parse_specifier_u(va_list *arg, t_conv *data);
char			*parse_specifier_x(va_list *arg, t_conv *data);
char			*parse_specifier_X(va_list *arg, t_conv *data);
char			*parse_specifier_percent(va_list *arg, t_conv *data);
char			*parse_specifier_o(va_list *arg, t_conv *data);
char			*parse_specifier_n(va_list *arg, t_conv *data);
#endif
