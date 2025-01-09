/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:00:30 by jheras-f          #+#    #+#             */
/*   Updated: 2019/12/19 15:43:13 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_with_zeros(char *str, char c, t_print *list)
{
	int		i;
	char	*tmpjoin1;
	char	*tmpjoin2;

	i = 0;
	if (list->negflag == 1)
		list->zeros--;
	while (i < list->zeros && list->zeros > 0)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	tmpjoin1 = ft_strjoin(str, list->aux);
	free(list->aux);
	list->aux = tmpjoin1;
	if (list->negflag == 1)
	{
		tmpjoin2 = ft_strjoin("-", list->aux);
		free(list->aux);
		list->aux = tmpjoin2;
	}
}

void	ft_set_spaces_right(char *str, char c, t_print *list)
{
	int		i;
	char	*tmpjoin1;
	char	*tmpjoin2;

	i = 0;
	if (list->negflag == 1)
	{
		tmpjoin1 = ft_strjoin("-", list->aux);
		free(list->aux);
		list->aux = tmpjoin1;
		list->spaces--;
	}
	while (i < list->spaces && list->spaces > 0)
		str[i++] = c;
	str[i] = '\0';
	tmpjoin2 = ft_strjoin(list->aux, str);
	free(list->aux);
	list->aux = tmpjoin2;
}

void	ft_set_spaces_left(char *str, char c, t_print *list)
{
	int		i;
	char	*tmpjoin1;
	char	*tmpjoin2;

	i = 0;
	if (list->negflag == 1)
	{
		tmpjoin1 = ft_strjoin("-", list->aux);
		if (list->aux != NULL)
		{
			free(list->aux);
			list->aux = NULL;
		}
		list->aux = tmpjoin1;
		list->spaces--;
	}
	while (i < list->spaces && list->spaces > 0)
		str[i++] = c;
	str[i] = '\0';
	tmpjoin2 = ft_strjoin(str, list->aux);
	if (list->aux != NULL)
	{
		free(list->aux);
		list->aux = NULL;
	}
	list->aux = tmpjoin2;
	//Revisa esto con cuidado. los test salen bien, pero tengo dudas de estar liberando bien. si dudas borra.
	
	//free(tmpjoin1);
	//tmpjoin1 = NULL;
	
}

void	ft_set_l_spaces_zeros(char *str, t_print *list)
{
	int		i;
	int		j;
	char	*tmpjoin1;

	i = 0;
	j = 0;
	if (list->negflag == 1)
		list->spaces--;
	while (i < list->spaces && list->spaces > 0)
		str[i++] = ' ';
	if (list->negflag == 1)
		str[i++] = '-';
	while (j < list->zeros && list->zeros > 0)
	{
		str[i++] = '0';
		j++;
	}
	str[i] = '\0';
	tmpjoin1 = ft_strjoin(str, list->aux);
	free(list->aux);
	list->aux = tmpjoin1;
}

void	ft_set_r_spaces_zeros(char *str, t_print *list)
{
	int		i;
	int		j;
	char	*tmpjoin1;
	char	*tmpjoin2;
	char	*tmpjoin3;

	i = 0;
	j = 0;
	if (list->negflag == 1)
		list->spaces--;
	while (i < list->spaces && list->spaces > 0)
		str[i++] = ' ';
	while (j < list->zeros && list->zeros > 0)
	{
		tmpjoin1 = ft_strjoin("0", list->aux);
		free(list->aux);
		list->aux = tmpjoin1;
		j++;
	}
	str[i] = '\0';
	if (list->negflag == 1)
	{
		tmpjoin2 = ft_strjoin("-", list->aux);
		free(list->aux);
		list->aux = tmpjoin2;
	}
	tmpjoin3 = ft_strjoin(list->aux, str);
	free(list->aux);
	list->aux = tmpjoin3;
}
