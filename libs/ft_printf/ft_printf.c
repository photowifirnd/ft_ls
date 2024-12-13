/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 09:46:07 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:27:16 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	ft_type(char *str, size_t *i, t_print *list)
{
	if (str[*i] == 'c')
		ft_print_char(list);
	else if (str[*i] == 'd' || str[*i] == 'i')
		ft_print_int(list);
	else if (str[*i] == 's')
		ft_print_str(list);
	else if (str[*i] == 'u')
		ft_print_uint(list);
	else if (str[*i] == 'p')
		ft_print_pointer(list);
	else if (str[*i] == 'x' || str[*i] == 'X')
		ft_print_hex(str, i, list);
	else if (str[*i] == '%')
		ft_print_percnt(list);
	(*i)++;
}

static int	ft_parser(t_print *list)
{
	size_t	i;

	i = 0;
	while (list->ost[i])
	{
		if (list->ost[i] == '%')
		{
			i++;
			ft_init_list(list);
			ft_parse_flags(&i, list);
			ft_type(list->ost, &i, list);
			free(list->aux);
			//free(list->tmp);
		}
		else
			while (list->ost[i] && list->ost[i] != '%')
			{
				ft_putchar(list->ost[i]);
				i++;
				list->len++;
			}
	}
	return (list->len);
}

int			ft_printf(const char *s, ...)
{
	t_print list;
	int		result;

	ft_bzero(&list, sizeof(0));
	va_start(list.pl, s);
	list.ost = (char *)ft_strdup(s);
	list.len = 0;
	result = ft_parser(&list);
	va_end(list.pl);
	free(list.ost);
	//free(list.tmp);
	//free(list.aux);
	/*list.ost = NULL;
	list.tmp = NULL;*/
	return (result);
}
