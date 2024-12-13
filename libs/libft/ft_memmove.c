/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 08:04:23 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/15 12:32:14 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*pdst;
	const char	*psrc;

	if (dst == NULL && src == NULL)
		return (NULL);
	pdst = dst;
	psrc = src;
	if (len != 0)
	{
		if (pdst < psrc)
		{
			while (len--)
				*pdst++ = *psrc++;
		}
		else
		{
			pdst += len - 1;
			psrc += len - 1;
			while (len--)
				*pdst-- = *psrc--;
		}
	}
	return (dst);
}
