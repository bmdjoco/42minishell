/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:49:20 by milo              #+#    #+#             */
/*   Updated: 2025/08/22 11:14:20 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

static int	check_char(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'x' || c == 'u' || c == 'X'
		|| c == '%')
		return (1);
	return (0);
}

int	print_str_fd(int fd, const char *format, va_list params)
{
	int	i;
	int	res;

	i = 0;
	res = i;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && check_char(format[i + 1]))
		{
			res = res + distrib(format[i + 1], params, fd);
			i = i + 2;
		}
		else
		{
			ft_putchar_fd(format[i], fd);
			res++;
			i++;
		}
	}
	return (res);
}

static int	distrib(char type, va_list params, int fd)
{
	int	i;

	i = 0;
	if (type == 'c')
		i = type_c(params, fd);
	if (type == 'd' || type == 'i')
		i = type_di(params, fd);
	if (type == 'u')
		i = type_u(params, fd);
	if (type == 's')
		i = type_s(params, fd);
	if (type == 'p')
		i = type_p(params, fd);
	if (type == 'x')
		i = type_x(params, fd);
	if (type == 'X')
		i = type_xx(params, fd);
	if (type == '%')
		i = type_percent(fd);
	return (i);
}

static int	check_format(const char *format)
{
	int	i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && check_char(format[i + 1] == 0))
			return (1);
		i++;
	}
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int	count;

	if (!format)
		return (-1);
	count = 0;
	va_list(params);
	va_start(params, format);
	if (check_format(format) == 1)
	{
		va_end(params);
		return (0);
	}
	count = print_str(fd, format, params);
	va_end(params);
	return (count);
}
