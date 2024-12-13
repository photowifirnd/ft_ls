/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:00:30 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:40:02 by jheras-f         ###   ########.fr       */
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

static void ft_fill_spaces(t_print *list)
{
	char	*tmp;
	int		sz;

	sz = (list->spaces > list->prze) ? list->spaces : list->prze;
	if (!(tmp = (char *)malloc((sizeof(char) * sz) + 1)))
		return ;
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
}

void		ft_print_int(t_print *list)
{
	long int val;

	free(list->aux);
	if (!(val = va_arg(list->pl, int)) && list->prze > 0)
		list->aux = ft_strdup("0");
	else if (list->prze == 0 && val == 0 && list->prec == 1)
		list->aux = ft_strdup("");
	else
	{
		if (val < 0)
		{
			val *= -1;
			list->negflag = 1;
		}
		list->aux = ft_itoa(val);
	}
	if (val == 2147483648)
	{
		free(list->aux);
		list->aux = ft_strtrim((char *)list->aux, (char *)"-");
	}
	ft_fill_spaces(list);
	list->len += ft_strlen(list->aux);
	ft_putstr(list->aux);
	free(list->aux);
	//free(list->tmp);
	list->aux = NULL;
	//list->tmp = NULL;
}
