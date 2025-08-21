/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:53:06 by jmellado          #+#    #+#             */
/*   Updated: 2025/07/04 19:54:21 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_handle_char(va_list ap);
int	ft_handle_string(va_list ap);
int	ft_handle_int(va_list ap);
int	ft_handle_unsigned(va_list ap);
int	ft_handle_pointer(va_list ap);
int	ft_handle_hexlower(va_list ap);
int	ft_handle_hexupper(va_list ap);
int	ft_handle_percent(void);
int	ft_putchar(char c);
int	ft_putnbr_base(unsigned long long nb, const char *base);

#endif
