/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:08:44 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/15 12:30:59 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	len;

	if (!s2 || !s1)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(len * sizeof(char) + 1);
	if (res != NULL)
	{
		while (*s1)
			*res++ = *s1++;
		while (*s2)
			*res++ = *s2++;
		*res = '\0';
		return (res - len);
	}
	return (NULL);
}
