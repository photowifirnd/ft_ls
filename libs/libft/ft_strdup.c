/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:29:00 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/15 12:30:46 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
    size_t	len;

    len = ft_strlen(s1);
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    ft_strcpy(dup, s1);
    return (dup);
	/*size_t	len;
	size_t	first;
	char	*cpy;

	len = ft_strlen(s1);
	first = len;
	if ((cpy = (char *)malloc(len * sizeof(char) + 1)))
	{
		while (len--)
			*cpy++ = (char)*s1++;
		*cpy = '\0';
		return (cpy - (first));
	}
	return (NULL);*/
}
