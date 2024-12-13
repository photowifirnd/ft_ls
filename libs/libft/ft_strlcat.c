/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:25:51 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/19 07:56:18 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned	int		dest_len;
	unsigned	int		src_len;

	if (dstsize < (unsigned)ft_strlen(dst))
		dest_len = dstsize;
	else
		dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len == dstsize)
		return (dstsize + src_len);
	if (src_len < dstsize - dest_len)
		ft_strncat(dst, src, src_len + 1);
	else
	{
		ft_strncat(dst, src, dstsize - dest_len - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dest_len + src_len);
}
