/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 12:42:02 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:27:49 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct		s_print
{
	char			*ost;
	char			*aux;
//	char			*tmp;
	int				parsflag;
	int				negflag;
	int				zeros;
	int				prze;
	int				spaces;
	int				align;
	int				zalign;
	int				prec;
	int				len;
	int				val;
	unsigned int	uval;
	unsigned long	pval;
	va_list			pl;
}					t_print;

void				ft_init_list(t_print *list);
void				ft_print_char(t_print *list);
void				ft_print_int(t_print *list);
void				ft_print_str(t_print *list);
void				ft_print_uint(t_print *list);
void				ft_print_pointer(t_print *list);
void				ft_print_hex(const char *str, size_t *i, t_print *list);
void				ft_print_percnt(t_print *list);
char				*ft_set_value_asterisk(size_t *i, t_print *list);
void				ft_set_with_zeros(char *str, char c, t_print *list);
void				ft_set_spaces_right(char *str, char c, t_print *list);
void				ft_set_spaces_left(char *str, char c, t_print *list);
void				ft_set_l_spaces_zeros(char *str, t_print *list);
void				ft_set_r_spaces_zeros(char *str, t_print *list);
void				ft_set_zeros_width(size_t *i, t_print *list);
void				ft_set_zeros_prec(size_t *i, t_print *list);
void				ft_parse_flags(size_t *i, t_print *list);
void				ft_parse_asterisk(t_print *list, size_t *i);
void				ft_parse_neg_prec(t_print *list, size_t *i);
void				ft_parse_neg_noprec(t_print *list, size_t *i);
void				ft_parse_zero(t_print *list, size_t *i);
int					ft_printf(const char *s, ...);

#endif
