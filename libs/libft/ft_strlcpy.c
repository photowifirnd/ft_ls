/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:27:31 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/19 07:53:55 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*psrc;
	size_t		sz;

	psrc = src;
	sz = dstsize;
	if (!src)
		return (0);
	if (sz)
	{
		while (--sz)
		{
			if ((*dst++ = *src++) == '\0')
				break ;
		}
	}
	if (sz == 0)
	{
		if (dstsize)
			*dst = '\0';
		while (*src++)
			;
	}
	return (src - psrc - 1);
}
