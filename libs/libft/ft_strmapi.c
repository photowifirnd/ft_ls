/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:31:42 by jheras-f          #+#    #+#             */
/*   Updated: 2019/11/15 12:34:38 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*func;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((func = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
	{
		while (s[i] != '\0')
		{
			func[i] = f(i, s[i]);
			i++;
		}
		func[i] = '\0';
		return (func);
	}
	return (NULL);
}
