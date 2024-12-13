/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percnt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:28:44 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:25:20 by jheras-f         ###   ########.fr       */
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
	else if (list->zeros <= (int)(ft_strlen(list->aux)))
	{
		list->spaces = 0;
		list->zeros = 0;
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

	sz = (list->spaces > list->prze) ? list->spaces : list->prze;
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

void		ft_print_percnt(t_print *list)
{
	list->aux = ft_strdup("%");
	list->aux = ft_fill_spaces(list);
	list->len += ft_strlen(list->aux);
	ft_putstr(list->aux);
	free(list->aux);
//	free(list->tmp);
	list->aux = NULL;
//	list->tmp = NULL;
	ft_init_list(list);
}
