/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 09:45:13 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/15 12:30:16 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_units(int n)
{
	int i;
	int div;

	div = 1000000000;
	i = 0;
	while (div)
	{
		if (n / div != 0)
			i++;
		div /= 10;
	}
	return (i);
}

static char		*ft_reverse(char *s1, int aux)
{
	char	*ps;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	ps = (char *)malloc(aux + 1);
	while (s1[i] != '\0')
	{
		ps[j] = s1[i];
		j--;
		i++;
	}
	ps[i] = '\0';
	return (ps);
}

static char		*ft_extract(char *s1, int n, int flag, int aux)
{
	int count;

	count = ft_count_units(n);
	while (count--)
	{
		*++s1 = 48 + (n % 10);
		n /= 10;
	}
	(flag) && (*++s1 = '-');
	*++s1 = '\0';
	return (s1 - aux);
}

char			*ft_itoa(int n)
{
	char	*c;
	int		aux;
	int		flag;

	aux = ft_count_units(n);
	flag = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n < 0)
	{
		flag = 1;
		n *= -1;
		aux++;
	}
	else if (n == 0)
		return (ft_strdup("0"));
	if (!(c = (char *)malloc(sizeof(char) * aux + 2)))
		return (NULL);
	char *ret = ft_reverse(ft_extract(c, n, flag, aux), aux);
	free(c);
	c = NULL;
	return (ret);
}
