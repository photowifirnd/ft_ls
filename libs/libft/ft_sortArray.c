/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortArray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 14:24:35 by jheras-f          #+#    #+#             */
/*   Updated: 2025-01-08 14:24:35 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_sortArray(char **arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				char *temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}