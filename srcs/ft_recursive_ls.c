/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-16 13:51:16 by jheras-f          #+#    #+#             */
/*   Updated: 2025-01-16 13:51:16 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ft_free_recursive(t_content **node) {
    if ((*node)->subdir != NULL)
    {
        free_content_dir(&(*node)->subdir);
    }
    free_content_dir(node);
}
int ft_print_info_recursive(t_content **entry, t_flags flags, int count)
{
    t_content *current;
    t_columns columns;
    int is_new_line = 0;
    int no_directory = 0;
    ft_calculate_widths(&columns, entry);
    if (entry == NULL || *entry == NULL){
        return (SUCCESS);
	}
    current = (*entry)->begin;
    //is_new_line = ft_print_files_in_args(entry, flags, columns);
    current = (*entry)->begin;
    current = (flags.r) ? (*entry)->end : (*entry)->begin;
    /**
     * 0: no regular files where found in arguments
     * 1: regular files where found in arguments
     */
    while (current != NULL)
    {
        if (is_new_line == 1 && current->file_description->type == 'd')
        {
            ft_printf("\n");
            no_directory = 1;
        }
        // Handle the -l flag: Print detailed information
        if (flags.l)
        {
            if (current->file_description->type == 'd')
            {
                if (count > 1){
                    ft_printf("%s:\n", current->file_description->fname);
                }
                ft_printf("total: %d\n", current->blk_total);
            }
            if (current->subdir != NULL)
            {
                ft_print_subdir(&current->subdir, flags);
                //should print new line if there are more directories to print but only if is_new_line is false
                if (current->next != NULL && current->next->file_description->type == 'd' && !is_new_line)
                {
                    ft_printf("\n");
                }
            }
        }
        else
        {
            if (current->file_description->type == 'd' && count > 1)
            {
                if (is_new_line == 1)
                {
                    ft_printf("\n");
                    is_new_line = 0;
                }
                ft_printf("%s:\n", current->file_description->fname);
            }
            else if (current->file_description->type == 'd'&& flags.R)
            {
                if (is_new_line == 1)
                {
                    ft_printf("\n");
                    is_new_line = 0;
                }
                ft_printf("%s:\n", current->file_description->fname);
                if (current->subdir == NULL)
                {
                    ft_printf("\n");
                }
            }
            if (current->subdir != NULL)
            {
                t_content *subdir;

                /* ft_printf("\n%s:\n",current->file_description->fname); */
                subdir = (flags.r) ? current->subdir->end : current->subdir->begin;
                while (subdir != NULL){
                    if (subdir->name[0] == '.' && !flags.a)
                    {
                        subdir = (flags.r) ? subdir->prev : subdir->next;
                        continue;
                    }
                    ft_printf("%s", subdir->file_description->fname);
                    if ((subdir->next != NULL && !flags.r) || (subdir->prev != NULL && flags.r))
                    {
                        ft_printf("  ");
                    }
                    subdir = (flags.r) ? subdir->prev : subdir->next;
                }
                ft_printf("\n");
                
                /* if (flags.R && current->file_description->type == 'd')
                {
                    ft_printf("????\n");
                } */
                if ((!flags.r && current->next != NULL) || (flags.r && current->prev != NULL && current->prev->file_description->type == 'd'))
                {
                    ft_printf("\n");
                }
            }
            if (flags.R && current->subdir != NULL)
            {
                
                ft_recursive(current, flags);
            }
        }
        current = (flags.r) ? current->prev : current->next;
    }
    if (!no_directory && is_new_line && !flags.l)
    {
        ft_printf("\n");
    }
    return (SUCCESS);
}
int ft_recursive(t_content *dir, t_flags flags)
{
    t_content *current;
	if (dir == NULL || dir->subdir == NULL)
	{
		return EXIT_FAILURE;
	}
	current = (flags.r) ? dir->subdir->end : dir->subdir->begin;
    
	while (current != NULL)
	{
		if (current->file_description->type == 'd' && ft_strcmp(current->name, ".") != 0 && ft_strcmp(current->name, "..") != 0)
		{
            t_content *newNode = new_container(current->file_description->path);
            if ((ft_fill_description(current->file_description->path, &newNode)) == EXIT_FAILURE)
            {
                ft_printf("Failed to set file description for %s\n", current->file_description->path);
                ft_free_recursive(&newNode);
                continue;
                //return EXIT_FAILURE; // Or should continue?
            }
            if ((ft_query_dir(&newNode, flags)) == EXIT_FAILURE)
				{
					ft_printf("Failed to query directory %s\n", current->name);
                    ft_free_recursive(&newNode);
                    continue;
					//return (EXIT_FAILURE); // Or should continue?
				}
            ft_print_info_file(&newNode, flags, 1); // if EXIT_FAILURE, should we continue?
            ft_free_recursive(&newNode);
		}
        
		current = (flags.r) ? current->prev : current->next;
	}
    return EXIT_SUCCESS;
}