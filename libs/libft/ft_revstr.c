/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:51:24 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/05 16:00:10 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_revstr(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = ft_strlen(str) - 1;
	j = 0;
	tmp = ft_strdup(str);
	while (i >= 0)
	{
		tmp[j] = str[i];
		i--;
		j++;
	}
	j = 0;
	while (tmp[j] != '\0')
	{
		str[j] = tmp[j];
		j++;
	}
	free(tmp);
	tmp = NULL;
	return (str);
}
