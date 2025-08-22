/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:56:33 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/22 16:43:32 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_fprintf.h"

size_t	ft_strlens(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstrs_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlens(s));
}

void	ft_putnbr_fd(int nb, int fd)
{
	long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nb = -nb;
		nbr = -nbr;
		ft_putchar_fd('-', fd);
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}
