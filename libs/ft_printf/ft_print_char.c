/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:20:43 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/18 13:36:45 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_set_field(t_print *list)
{
	if (list->align == 0 && list->zalign == 1 && list->prec == 0)
	{
		list->zeros = list->spaces - ft_strlen(list->aux);
		list->spaces = 0;
	}
	else if (list->prze >= (int)(ft_strlen(list->aux)))
	{
		list->spaces = list->zeros - (ft_strlen(list->aux) +
				(list->prze - ft_strlen(list->aux)));
		list->zeros = list->zeros - list->spaces - ft_strlen(list->aux);
	}
	else
	{
		list->spaces = list->zeros - ft_strlen(list->aux);
		list->zeros = 0;
	}
}

static char	*ft_fill_spaces(t_print *list)
{
	char	*tmp;
	int		sz;

	sz = (list->spaces > list->prze ? list->spaces : list->prze);
	if (!(tmp = (char *)malloc((sizeof(char) * sz) + 1)))
		return (NULL);
	ft_set_field(list);
	if (list->zalign && !list->align && !list->prec)
		ft_set_with_zeros(tmp, '0', list);
	else if (list->align && !list->prec)
		ft_set_spaces_right(tmp, ' ', list);
	else if (list->prec && !list->align)
		ft_set_l_spaces_zeros(tmp, list);
	else if (!list->align && !list->zalign && !list->prec)
		ft_set_spaces_left(tmp, ' ', list);
	else if (list->align && list->prec)
		ft_set_r_spaces_zeros(tmp, list);
	free(tmp);
	tmp = NULL;
	return (list->aux);
}

static void	ft_set_null(t_print *list)
{
	size_t	i;

	i = 0;
	list->aux = ft_strdup("");
	list->aux = ft_fill_spaces(list);
	if (list->spaces == 0)
		list->len += 2;
	if (!list->align)
	{
		while (i < ft_strlen(list->aux) - 1 && *list->aux)
			ft_putchar(*list->aux++);
		ft_putchar('\0');
	}
	else
	{
		ft_putchar('\0');
		while (i < ft_strlen(list->aux) - 1 && *list->aux)
			ft_putchar(*list->aux++);
	}
	list->len += ft_strlen(list->aux) + list->spaces - 1;
}

void		ft_print_char(t_print *list)
{
	int		val;

	if (!(val = (unsigned char)(va_arg(list->pl, int))))
		ft_set_null(list);
	else
	{
		if (list->aux != NULL)
			free(list->aux);
		list->aux = ft_atos(val);
		
		list->aux = ft_fill_spaces(list);
		list->len += ft_strlen(list->aux);
		ft_putstr(list->aux);
	}
	if (list->aux != NULL)
		free(list->aux);
	list->aux = NULL;
	ft_init_list(list);
}
