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
            ft_printf("\n");
        }
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
            ft_print_info_file(&newNode, flags, 1, 1); // if EXIT_FAILURE, should we continue?
            ft_free_recursive(&newNode);
		}
		current = (flags.r) ? current->prev : current->next;
	}
    return EXIT_SUCCESS;
}