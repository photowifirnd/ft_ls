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
	ft_printf("file -> %s\n", (*entry)->name);
    current = (*entry)->begin;
    is_new_line = 0;
    
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
                if ((!flags.r && current->next != NULL) || (flags.r && current->prev != NULL && current->prev->file_description->type == 'd'))
                {
                    ft_printf("\n");
                }
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
int ft_open_recursive_dir(t_content **content_dir, const char *path, t_flags flags)
{
	char full_path[4096];
    DIR *dir;
    struct dirent *sdir;
    t_content *current = (*content_dir);
    t_content *new_node;
    
    if (!(dir = opendir(path))) {
        return ft_deny_access(path);
    }
    while ((sdir = readdir(dir)) != NULL)
    {
        // Skip the current and parent directory entries
        if (flags.a == 0 && sdir->d_name[0] == '.')
            continue;
        ft_get_full_path(full_path, (*content_dir)->file_description->path, sdir->d_name);
        new_node = new_container(sdir->d_name);
        ft_fill_description(full_path, &new_node);
        current->blk_total += new_node->file_description->blocks;
        // Add the directory entry name to the content list
        if (flags.t){
            if (ft_add_new_node_by_time(&current->subdir, new_node) == EXIT_FAILURE)
            {
                ft_printf("Failed to add new node for %s\n", sdir->d_name);
                closedir(dir);
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (ft_add_new_node_alphanumeric(&current->subdir, new_node) == EXIT_FAILURE)
            {
                ft_printf("Failed to add new node for %s\n", sdir->d_name);
                closedir(dir);
                return EXIT_FAILURE;
            } 
        }
    }
    closedir(dir);
	
    return EXIT_SUCCESS;
}
void ft_get_recursive_dir_content(t_content **r_subdir, const char *path, t_flags flags)
{
   /*  DIR *dir;
    struct dirent *entry;
    char full_path[4096]; */
	(void)path;
	(void)flags;
	t_content *tmp = (*r_subdir);
	
	while (tmp != NULL){
		if (tmp->file_description->type == 'd')
		{
			ft_printf("Recursive -> %s:\n", tmp->file_description->path);
			ft_open_recursive_dir(&tmp, tmp->file_description->path, flags);
			if (tmp->subdir != NULL)
			{
				t_content *subdir = tmp->subdir->begin;
				
					//ft_print_info_file(&subdir, flags, 1);

					subdir = subdir->next;
			}else{
				ft_printf("No subdirs\n");
			}
			
		}
		tmp = tmp->next;
	}
	
	/* if (flags.R && tmp->file_description->type == 'd')
	{
            t_content *subdir = NULL;
            ft_get_recursive_dir_content(&subdir, full_path, flags);
            (*container)->end->subdir = subdir;
	} */
}
void ft_recursive(t_content *dir, t_flags flags)
{
	if (dir == NULL || dir->subdir == NULL)
	{
		return ;
	}
	t_content *current = dir->subdir->begin;
	while (current != NULL)
	{
		if (current->file_description->type == 'd')
		{
			/**
			 * 
			 * 
			 * 
			 * HASTA AQIUI
			 * SE PUEDE HACER CONTROL-Z
			 * 
			 * 
			 * 
			 */
			//ft_printf("Recursive -> %s:\n", current->file_description->path);
			ft_open_recursive_dir(&current, current->file_description->path, flags);
			if (current->subdir){
				t_content * aux = current->subdir->begin;
				while (aux != NULL)
				{
					ft_print_info_recursive(&aux, flags, 1);
					aux = aux->next;
				}
				
			//ft_print_info_file(&current->subdir, flags, 0);
			} else {
				ft_printf("No subdirs\n");
			}
			ft_recursive(current, flags);
		}	
		current = current->next;
	}
}
/*t_content *new_node = new_container(current->file_description->fname);
ft_fill_description(current->file_description->path, &new_node);
ft_print_info_recursive(&new_node, flags, 1);*/