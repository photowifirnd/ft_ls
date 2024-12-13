/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 07:53:38 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 13:30:05 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_spaces_right(char *str, char c, t_print *list)
{
	int i;
	char	*tmpjoin;

	i = 0;
	while (i < list->spaces && list->spaces > 0)
		str[i++] = c;
	str[i] = '\0';
	if (list->align)
		tmpjoin = ft_strjoin(list->aux, str);
	else
		tmpjoin = ft_strjoin(str, list->aux);
	free(list->aux);
	list->aux = tmpjoin;
}

void	ft_spaces_left(char *str, char c, t_print *list)
{
	int		i;
	char	*tmpjoin;

	i = 0;
	while (i < list->spaces && list->spaces > 0)
		str[i++] = c;
	str[i] = '\0';
	tmpjoin = ft_strjoin(str, list->aux);
	free(list->aux);
	list->aux = tmpjoin;
}
