/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 07:31:02 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:26:48 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_init_list(t_print *list)
{
	list->aux = ft_strdup("");
	//list->tmp = ft_strdup("");
	list->negflag = 0;
	list->parsflag = 0;
	list->zeros = 0;
	list->prze = 0;
	list->spaces = 0;
	list->align = 0;
	list->zalign = 0;
	list->prec = 0;
	list->val = 0;
	list->uval = 0;
	list->pval = 0;
}

static void	ft_parse_num(char *str, size_t *i, t_print *list)
{
	char	*tmp;
	char	*tmpatos;

	while (str[*i] >= '0' && str[*i] <= '9' && str[*i] != '\0')
	{
		tmpatos = ft_atos(str[*i]);
		tmp = ft_strjoin(list->aux, tmpatos);
		free(tmpatos);
		free(list->aux);
		list->aux = ft_strdup(tmp);
		free(tmp);
		(*i)++;
	}
}

void		ft_set_zeros_width(size_t *i, t_print *list)
{
	ft_parse_num(list->ost, i, list);
	if (ft_strlen(list->aux) > 0)
		list->zeros = ft_atoi(list->aux);
	list->spaces = list->zeros;
	free(list->aux);
	list->aux = ft_strdup("");
	if (list->ost[*i] == '.' || list->ost[*i] == '*')
		ft_parse_flags(i, list);
}

void		ft_set_zeros_prec(size_t *i, t_print *list)
{
	(*i)++;
	list->prec = 1;
	list->zalign = 0;
	ft_parse_flags(i, list);
	ft_parse_num(list->ost, i, list);
	if (ft_strlen(list->aux) > 0)
		list->prze = ft_atoi(list->aux);
	free(list->aux);
	list->aux = NULL;
}

void		ft_parse_flags(size_t *i, t_print *list)
{
	while ((list->ost[*i] == '-' || (list->ost[*i] == '0' && !list->prec)
			|| list->ost[*i] == '.' || list->ost[*i] == '*') && list->ost[*i])
	{
		if (list->ost[*i] == '*')
			ft_parse_asterisk(list, i);
		if (list->ost[*i] == '-' && list->prec)
			ft_parse_neg_prec(list, i);
		if (list->ost[*i] == '-' && list->prec == 0)
			ft_parse_neg_noprec(list, i);
		if (list->ost[*i] == '0' && list->align == 0 && list->prec == 0)
			ft_parse_zero(list, i);
		if (list->ost[*i] == '0' && list->align)
			(*i)++;
		if (list->ost[*i] == '.' && list->prec == 0)
			ft_set_zeros_prec(i, list);
	}
	if (list->prec == 0 && list->ost[*i] != '%')
		ft_set_zeros_width(i, list);
}
