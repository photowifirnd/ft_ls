/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:04:26 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:28:13 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_set_width(t_print *list, int sel)
{
	if (sel == 1)
	{
		if (list->spaces > (int)ft_strlen(list->aux))
			list->spaces = list->spaces - ft_strlen(list->aux);
		else
			list->spaces = 0;
	}
	else if (sel == 2)
	{
		if (list->prze && !list->negflag)
			if ((int)(ft_strlen(list->aux)) > list->prze)
				list->spaces -= list->prze;
			else
				list->spaces -= ft_strlen(list->aux);
		else if (list->negflag)
		{
			list->prze = ft_strlen(list->aux);
			list->spaces -= ft_strlen(list->aux);
		}
		else
			list->spaces = list->zeros;
	}
}

static void	ft_place_spaces(char *str, char c, t_print *list)
{
	int i;

	i = 0;
	while (i < list->spaces && list->spaces > 0)
		str[i++] = c;
	str[i] = '\0';
	if (list->align)
		list->aux = ft_strjoin(list->aux, str);
	else
		list->aux = ft_strjoin(str, list->aux);
}

static void	ft_set_field(char *tmp, t_print *list)
{
	if ((list->align == 0 && list->prec == 0)
		|| (list->align == 1 && list->prec == 0))
		ft_set_width(list, 1);
	else if (list->align == 1 && list->prec == 1)
		ft_set_width(list, 2);
	else if (list->align == 0 && list->prec == 1)
	{
		if (list->negflag == 1)
			list->prze = ft_strlen(list->aux);
		else if ((int)(ft_strlen(list->aux)) > list->prze)
			list->spaces -= list->prze;
		else
			list->spaces -= ft_strlen(list->aux);
	}
	if (list->prec == 1)
		list->aux = ft_substr(list->aux, 0, list->prze);
	ft_place_spaces(tmp, ' ', list);
}

static void ft_fill_spaces(t_print *list)
{
	char	*tmp;
	int		sz;

	sz = (list->spaces > list->prze) ? list->spaces : list->prze;
	if (!(tmp = (char *)malloc((sizeof(char) * sz) + 1)))
		return ;
	ft_set_field(tmp, list);
	free(tmp);
	tmp = NULL;
}

void		ft_print_str(t_print *list)
{
	free(list->aux);
	if (!(list->aux = va_arg(list->pl, char *)))
		list->aux = ft_strdup("(null)");
	ft_fill_spaces(list);
	list->len += ft_strlen(list->aux);
	ft_putstr(list->aux);
	free(list->aux);
//	free(list->tmp);
	list->aux = NULL;
//	list->tmp = NULL;
}
