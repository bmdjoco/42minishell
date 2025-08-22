/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:07:23 by bdjoco            #+#    #+#             */
/*   Updated: 2025/08/22 11:29:40 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int	size_calcu(long n);
int	type_percent(int fd);
int	type_c(va_list params, int fd);
int	type_s(va_list params, int fd);
int	type_u(va_list params, int fd);
int	type_p(va_list params, int fd);
int	type_x(va_list params, int fd);
int	type_di(va_list params, int fd);
int	type_xx(va_list params, int fd);
int	ft_putnbr_hex_up_fd(unsigned int nbr, int fd);
int	ft_putnbr_hex_low_fd(unsigned int nbr, int fd);
int	ft_putnbr_hex_adr_fd(unsigned long nbr, int fd);

void	ft_putchar_fd(char c, int fd);
void	fill_hex(char *dest, char *str);
void	ft_put_unsigned_nbr_fd(unsigned int nbr, int fd);

#endif
