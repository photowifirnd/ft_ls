/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-31 16:36:58 by jheras-f          #+#    #+#             */
/*   Updated: 2024-12-31 16:36:58 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void ft_free_alloc(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}