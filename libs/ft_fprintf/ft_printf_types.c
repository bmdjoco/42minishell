/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:51:01 by milo              #+#    #+#             */
/*   Updated: 2025/08/22 11:15:22 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

int	type_c(va_list params, int fd)
{
	char	c;

	c = (char)va_arg(params, int);
	ft_putchar_fd(c, fd);
	return (1);
}

int	type_di(va_list params, int fd)
{
	int	i;
	int	j;

	i = va_arg(params, int);
	j = size_calcu(i);
	ft_putnbr_fd(i, fd);
	return (j);
}

int	type_s(va_list params, int fd)
{
	char	*dup;
	int		i;

	dup = va_arg(params, char *);
	if (!dup)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	i = ft_strlen(dup);
	ft_putstr_fd(dup, fd);
	return (i);
}

int	type_u(va_list params, int fd)
{
	unsigned int	i;
	int				j;

	i = va_arg(params, unsigned int);
	j = size_calcu(i);
	ft_put_unsigned_nbr_fd(i, fd);
	return (j);
}

int	type_p(va_list params, int fd)
{
	void			*arg;
	unsigned long	ptr;
	int				i;

	arg = va_arg(params, void *);
	if (arg == 0)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	ptr = (unsigned long)arg;
	ft_putstr_fd("0x", fd);
	i = 2;
	i = i + ft_putnbr_hex_adr_fd(ptr, fd);
	return (i);
}
