/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:07:23 by bdjoco            #+#    #+#             */
/*   Updated: 2025/09/22 12:03:35 by bdjoco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>

int	size_calcu(long n);
int	type_percent_fd(int fd);
int	type_c_fd(va_list params, int fd);
int	type_s_fd(va_list params, int fd);
int	type_u_fd(va_list params, int fd);
int	type_p_fd(va_list params, int fd);
int	type_x_fd(va_list params, int fd);
int	type_di_fd(va_list params, int fd);
int	type_xx_fd(va_list params, int fd);
int	ft_putnbr_hex_up_fd(unsigned int nbr, int fd);
int	ft_putnbr_hex_low_fd(unsigned int nbr, int fd);
int	ft_putnbr_hex_adr_fd(unsigned long nbr, int fd);
int	ft_fprintf(int fd, const char *format, ...);

size_t	ft_strlens(const char *str);

void	ft_putstrs_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putchar_fd(char c, int fd);
void	fill_hex(char *dest, char *str);
void	ft_put_unsigned_nbr_fd(unsigned int nbr, int fd);

#endif
