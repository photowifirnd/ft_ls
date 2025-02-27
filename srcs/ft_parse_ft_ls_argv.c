/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_ft_ls_argv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-23 07:08:59 by jheras-f          #+#    #+#             */
/*   Updated: 2024-12-23 07:08:59 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_set_file(const char *path, int *file_count, char ***files)
{
	(*files)[*file_count] = malloc((ft_strlen(path) + 1) * sizeof(char));
	ft_strcpy((*files)[*file_count], path);
	(*file_count)++;
};
void init_flags(t_flags *flags)
{
	flags->l = 0;
	flags->a = 0;
	flags->r = 0;
	flags->t = 0;
	flags->R = 0;
	flags->is_flag = 0;
}

void ft_parse_ft_ls_argv(int argc, char *argv[], t_flags *flags, char ***files, int *file_count)
{
	int is_file = 0;
	*files = malloc(argc * sizeof(char *));
	*file_count = 0;
	init_flags(flags);

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && !is_file)
		{
			if (ft_strcmp(argv[i], "-") == 0){
				ft_set_file("-", file_count, files);
				is_file = 1;
			}
			else if (ft_strcmp(argv[i], "--") == 0)
				is_file = 1; 
			else if (argv[i][1] == '-')
			{
				ft_unrecognized_option(&argv[i][2]);
				return ;
			}
			else
			{
				for (int j = 1; argv[i][j] != '\0'; j++)
				{
					switch (argv[i][j])
					{
						case 'l': flags->l = 1; break;
						case 'a': flags->a = 1; break;
						case 'r': flags->r = 1; break;
						case 'R': flags->R = 1; break;
						case 't': flags->t = 1; break;
						default: ft_invalid_option(&argv[i][j]);
						return ;
					}
				}
			}
		}
		else
		{
			ft_set_file(argv[i], file_count, files);
			is_file = 1;
		}
	}
	if (*file_count == 0)
	{
		ft_set_file(".", file_count, files);
	}
	if (flags->l || flags->a || flags->r || flags->R || flags->t)
		flags->is_flag = 1;
}
