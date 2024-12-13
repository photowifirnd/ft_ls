/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultohex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:41:14 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/03 07:46:52 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(unsigned long nb)
{
	int i;

	i = 0;
	while (nb)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

static char		ft_getnum(unsigned long n)
{
	if (n <= 9)
		return ((char)(n + 48));
	else if (n > 9 && n < 16)
		return ((char)(n + 87));
	return (0);
}

char			*ft_ultohex(unsigned long nb)
{
	char	*str;
	int		i;
	int		len;
	int		nbase;

	nbase = 16;
	if (!nb)
		return (ft_strdup(""));
	len = ft_count(nb);
	if (!(str = (char *)malloc((len + 1) * sizeof(*str))))
		return (NULL);
	str[len] = '\0';
	i = len;
	while (nb)
	{
		i--;
		str[i] = ft_getnum(nb % nbase);
		nb /= nbase;
	}
	return (str);
}
