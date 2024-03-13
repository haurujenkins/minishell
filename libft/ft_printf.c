/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:35:22 by lle-pier          #+#    #+#             */
/*   Updated: 2024/01/12 16:30:58 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_which(const char *format, va_list args)
{
	int	i;

	i = 0;
	if (*format == 'c')
		i = char_print(va_arg(args, int));
	else if (*format == 's')
		i = str_print(va_arg(args, char *));
	else if (*format == 'i')
		i = int_print(va_arg(args, int));
	else if (*format == 'p')
		i = hex_print(va_arg(args, size_t));
	else if (*format == 'd')
		i = int_print(va_arg(args, int));
	else if (*format == 'u')
		i = uint_print(va_arg(args, unsigned int));
	else if (*format == 'x')
		i = hex_lower_print(va_arg(args, unsigned int));
	else if (*format == 'X')
		i = hex_upper_print(va_arg(args, unsigned int));
	else if (*format == '%')
		i = char_print('%');
	return (i);
}

static int	modulo(const char *format, va_list args, int i, int temp)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (mystrchr("cspdiuxX%", *format))
			{
				temp = ft_which(format, args);
				if (temp == -1)
					return (-1);
				else
					i += temp;
			}
		}
		else
		{
			temp = char_print(*format);
			if (temp == -1)
				return (-1);
			i += temp;
		}
		format++;
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;

	va_start(args, format);
	if (*format == '%' && *format + 1 == '\0')
		return (-1);
	i = modulo(format, args, 0, 0);
	va_end(args);
	return (i);
}
