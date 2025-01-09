/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-31 12:01:21 by jheras-f          #+#    #+#             */
/*   Updated: 2024-12-31 12:01:21 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
void ft_print_description(t_file *file_description){
    char *date;
    date = ft_strtrim(file_description->date, "\n");

    //ft_printf("%c", file_description->type);
    ft_printf("%s ", file_description->str_perm);
    ft_printf("%d ", file_description->nlink);
    ft_printf("%s ", file_description->str_owner);
    ft_printf("%s ", file_description->str_group);
    ft_printf("%d ", file_description->size);
    ft_printf("%s ", date);
    ft_printf("%s\n", file_description->fname);

    ft_free_alloc(date);
}
void ft_print_subdir(t_content **subdir)
{
    t_content *current = *subdir;
    while (current != NULL)
    {
        ft_printf("Checking file description - >%s\n", current->file_description->fname);
        ft_print_description(current->file_description);
        current = current->next;
    }
}
int ft_print_info_file(t_content **entry, t_flags flags)
{
    t_file *file_description;

    if (entry == NULL || *entry == NULL){
        return (SUCCESS);
	}
    t_content *current = (*entry)->begin;

    while (current != NULL)
    {
        file_description = current->file_description;

        // Handle the -a flag: Skip hidden files if -a is not set
        if (!flags.a && file_description->fname[0] == '.' && ft_strlen(file_description->fname) > 1)
        {
            current = current->next;
            continue;
        }

        // Handle the -l flag: Print detailed information
        if (flags.l)
        {
			t_content *subdir = current->subdir;
			ft_print_description(file_description);
			ft_print_subdir(&subdir);
        }
        else
        {
			//here you have to make a distinction between files and directories, if it is only one directory,
			// you have to print the files inside it
			// if it is a file, you have to print the file name
			// if there are several directories, you have to print the directory name: and the files inside it
			//this will be done outside of functrion, by calling print i.e. inside main function
            // Print only the file name if -l is not set
			ft_printf("Entering on else print with no flags:\n");
            t_content *subdir = current->subdir->begin;
            ft_printf("Checking file description - >");
            ft_printf("--->%s\n", file_description->fname);
			while (subdir != NULL){
				if (!flags.a && subdir->file_description->fname[0] == '.')
				{
					subdir = subdir->next;
					continue;
				}else {
					ft_printf("%s ", subdir->file_description->fname);
					subdir = subdir->next;
				}
                /* ft_printf("%s ", subdir->name);
                subdir = subdir->next; */
			}
			ft_printf("\n");
        }

        current = current->next;
    }

    return (SUCCESS);
}

int OLD_ft_print_info_file(t_content **entry)
{
	char *date;
	t_file *file_description;
	
	if (entry == NULL)
		return (SUCCESS);
	file_description = (*entry)->file_description;
	date = ft_strtrim(file_description->date, "\n");
	
	ft_printf("%c", file_description->type);
	ft_printf("%s ", file_description->str_perm);
	ft_printf("%d ", file_description->nlink);
	ft_printf("%s ", file_description->str_owner);
	ft_printf("%s\t", file_description->str_group);
	ft_printf("%d ", file_description->size);
	ft_printf("%s ", date);
	ft_printf("%s\n", file_description->fname);
	ft_free_alloc(date);
	
	return (EXIT_SUCCESS);
}