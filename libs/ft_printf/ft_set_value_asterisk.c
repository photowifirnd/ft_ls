/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_value_asterisk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:13:07 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 14:43:22 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_set_value_asterisk(size_t *i, t_print *list)
{
	int		len;
	char	*auxtmp;
	char	*tmp;

	len = ft_strlen(list->ost) - (*i);
	free(list->aux);
	list->val = va_arg(list->pl, int);
	tmp = ft_itoa(list->val);
	list->aux = (char *)malloc((sizeof(char) * (*i)) + 1);
	list->aux = ft_strncpy(list->aux, list->ost, (*i));
	list->aux[*i] = '\0';
	auxtmp = ft_strjoin(list->aux, tmp);
	free(tmp);
	free(list->aux);
	tmp = ft_substr(list->ost, (*i) + 1, len);
	list->aux = ft_strjoin(auxtmp, tmp);
	free(tmp);
	free(auxtmp);
	free(list->ost);
	list->ost = ft_strdup(list->aux);
	free(list->aux);
	list->aux = ft_strdup("");
	return ((char *)list->ost);
}
