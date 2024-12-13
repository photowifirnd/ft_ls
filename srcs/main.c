/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-11 12:21:21 by jheras-f          #+#    #+#             */
/*   Updated: 2024-12-11 12:21:21 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "ft_printf.h"

int main(int args, char *argv[])
{
	if (args > 1)
		ft_printf("Number of argumetns: %s\n",argv[1]);
	else
		ft_putstr("Hello World\n");
	return (0);
}