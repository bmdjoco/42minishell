/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:23:10 by miltavar          #+#    #+#             */
/*   Updated: 2025/08/22 11:29:34 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

int	ft_putnbr_hex_adr(unsigned long nbr, int fd)
{
	char	hex[17];
	char	buffer[16];
	int		i;
	int		count;

	fill_hex(hex, "0123456789abcdef");
	if (nbr == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	i = 0;
	while (nbr > 0)
	{
		buffer[i++] = hex[nbr % 16];
		nbr /= 16;
	}
	count = i;
	while (--i >= 0)
		ft_putchar_fd(buffer[i], 1);
	return (count);
}

int	type_x(va_list params, int fd)
{
	unsigned int	i;
	int				j;

	i = va_arg(params, int);
	j = ft_putnbr_hex_low(i, fd);
	return (j);
}

int	type_xx(va_list params, int fd)
{
	unsigned int	i;
	int				j;

	i = va_arg(params, int);
	j = ft_putnbr_hex_up(i, fd);
	return (j);
}

int	type_percent(int fd)
{
	ft_putchar_fd('%', fd);
	return (1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(1, &c, fd);
}
