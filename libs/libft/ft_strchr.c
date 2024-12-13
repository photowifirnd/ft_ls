/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:19:44 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/15 12:30:31 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *ps;

	ps = (char *)s;
	if (c == '\0')
		return (ps + ft_strlen(ps));
	while (*ps)
	{
		if (*ps == c)
			return (ps);
		ps++;
	}
	return (NULL);
}
