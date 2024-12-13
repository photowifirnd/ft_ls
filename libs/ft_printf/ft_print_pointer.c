/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:35:33 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:25:46 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_set_field(t_print *list)
{
	if (list->align == 1)
	{
		list->zeros = list->spaces - ft_strlen(list->aux);
		list->spaces = list->spaces - ft_strlen(list->aux);
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

	if (!(tmp = (char *)malloc((sizeof(char) * list->spaces) + 3)))
		return (NULL);
	ft_set_field(list);
	if (list->align)
		ft_set_spaces_right(tmp, ' ', list);
	else if (!list->align)
		ft_set_spaces_left(tmp, ' ', list);
	free(tmp);
	tmp = NULL;
	return (list->aux);
}

void		ft_print_pointer(t_print *list)
{
	if (!(list->pval = va_arg(list->pl, unsigned long)) && !list->prec)
		list->aux = ft_atos('0');
	else if (!list->pval && list->prec && !list->prze)
		list->aux = ft_strdup("");
	else
		list->aux = ft_ultohex(list->pval);
	list->aux = ft_strjoin("0x", list->aux);
	list->aux = ft_fill_spaces(list);
	list->len += ft_strlen(list->aux);
	ft_putstr(list->aux);
	free(list->aux);
	//free(list->tmp);
	list->aux = NULL;
//	list->tmp = NULL;
	ft_init_list(list);
}
