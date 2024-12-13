/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:20:25 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:24:09 by jheras-f         ###   ########.fr       */
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

static void	ft_is_zero(t_print *list)
{
	if (list->prze > 0)
		list->aux = ft_atos('0');
	else if (list->spaces > 0 && !list->prec)
		list->aux = ft_atos('0');
	else if (!list->zalign && !list->prec && !list->align)
		list->aux = ft_atos('0');
	else if (list->prze == 0 && list->pval == 0 && list->prec == 1)
		list->aux = ft_strdup("");
}

void		ft_print_hex(const char *str, size_t *i, t_print *list)
{
	int				j;

	list->aux = NULL;
	if (!(list->pval = (unsigned long)va_arg(list->pl, unsigned long)))
		ft_is_zero(list);
	else
		list->aux = ft_ultohex(list->pval);
	j = 0;
	if (str[*i] == 'X')
	{
		while (list->aux[j] != '\0')
		{
			list->aux[j] = ft_toupper(list->aux[j]);
			j++;
		}
	}
	list->aux = ft_fill_spaces(list);
	list->len += ft_strlen(list->aux);
	ft_putstr(list->aux);
	free(list->aux);
	//free(list->tmp);
	list->aux = NULL;
	//list->tmp = NULL;
	//ft_init_list(list);
}
