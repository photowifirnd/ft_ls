/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:49:49 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/15 12:33:27 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ps;
	int		i;

	ps = (char *)s;
	i = ft_strlen(s) - 1;
	ps = ps + i;
	if ((unsigned char)c == '\0' && ft_strlen(ps) != 0)
		return (ps + ft_strlen(ps));
	if ((unsigned char)c == '\0' && ft_strlen(ps) == 0)
		return (ps + ft_strlen(ps) + 1);
	while (*s)
	{
		if (*ps == (char)c)
			return (ps);
		ps--;
		s++;
	}
	return (NULL);
}
