/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 11:50:42 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 13:41:59 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_asterisk(t_print *list, size_t *i)
{
	char	*auxtmp;

	auxtmp = (char *)ft_set_value_asterisk(i, list);
	list->ost = auxtmp;
}

void	ft_parse_neg_prec(t_print *list, size_t *i)
{
	(*i)++;
	list->negflag = 1;
	while (list->ost[*i] >= '0' && list->ost[*i] <= '9'
			&& list->ost[*i] != '\0')
		(*i)++;
}

void	ft_parse_neg_noprec(t_print *list, size_t *i)
{
	list->align = 1;
	list->zalign = 0;
	(*i)++;
}

void	ft_parse_zero(t_print *list, size_t *i)
{
	list->align = 0;
	list->zalign = 1;
	(*i)++;
}
