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
void ft_get_columns_size(t_columns *cols, t_content **container)
{
    int len;
    t_content *current = (*container)->begin;

    (cols)->nlink = 0;
    (cols)->owner = 0;
    (cols)->group = 0;
    (cols)->size = 0;
    while (current != NULL)
    {
        if (current->file_description->nlink > (cols)->nlink)
            (cols)->nlink = current->file_description->nlink;
        if ((len = ft_strlen(current->file_description->str_owner)) > (cols)->owner)
            (cols)->owner = len;
        if ((len = ft_strlen(current->file_description->str_group)) > (cols)->group)
            (cols)->group = len;
        if (current->file_description->size > (cols)->size)
            (cols)->size = current->file_description->size;
        current = current->next;
    }
}
void ft_calculate_widths(t_columns *columns, t_content **subdir)
{
    char *width_len;

    ft_get_columns_size(columns, subdir);
    width_len = ft_itoa(columns->size);
    columns->size = ft_strlen(width_len);
    ft_free_alloc(width_len);
    width_len = ft_itoa(columns->nlink);
    columns->nlink = ft_strlen(width_len);
    ft_free_alloc(width_len);
}
//Print the detailed information of a file when the -l flag is set
void ft_print_description(t_file *file_description, t_columns columns)
{
    char *date;
    date = ft_strtrim(file_description->date, "\n");
    ft_printf("%s ", file_description->str_perm);
    ft_printf("%-*d ", columns.nlink, file_description->nlink);
    ft_printf("%-*s ", columns.owner, file_description->str_owner);
    ft_printf("%-*s ", columns.group, file_description->str_group);
    ft_printf("%*d ", columns.size, file_description->size);
    
    ft_printf("%s ", date);
    ft_printf(">>>> %d ", file_description->timestamp);
    if (file_description->type == 'l')
    {
        ft_printf("%s -> %s\n", file_description->fname, file_description->link);
    }
    else {
        ft_printf("%s\n", file_description->fname);
    }
    ft_free_alloc(date);
}
//print files in the container, not directories: intended for files passed as arguments
int ft_print_files_in_args(t_content **container, t_flags flags, t_columns columns)
{
    t_content *current = *container;
    t_content *tmp = NULL;
    t_content *new_node;

    int ret = 0;
    
    current = (flags.r) ? current->end : current->begin;
    while ( current != NULL)
    {
        if (current->file_description->type != 'd')
        {
        //ft_printf("Current file: %s\n", current->name);
            if (flags.is_flag && flags.l)
            {
                ft_print_description(current->file_description, columns);
            }
            else
            {
                new_node = new_container(current->file_description->fname);
                
                ft_add_new_node(&tmp, new_node); 
                //ft_printf("%s", current->file_description->fname);
            }
            ret = 1;
        }
        current = (flags.r) ? current->prev : current->next;
    }
    if (tmp == NULL)
        return ret;
    current = tmp->begin;
    while (current != NULL)
    {
        ft_printf("-->%s", current->name);
        if (current->next != NULL)
        {
            ft_printf("  ");
        }
        current = current->next;
    }
    
    free_content_dir(&tmp);
    return ret;
}
//print files and directories in the given container: Intended for listing subdir content
void ft_print_subdir(t_content **subdir, t_flags flags)
{
    t_content *current;
    t_columns columns;
    
    current = (flags.r) ? (*subdir)->end : (*subdir)->begin;
    ft_calculate_widths(&columns, subdir);
    while (current != NULL)
    {
        if (current->name[0] == '.' && !flags.a)
        {
            current = (flags.r) ? current->prev : current->next;
            continue;
        }
        ft_print_description(current->file_description, columns);
        current = (flags.r) ? current->prev : current->next;
    }
}
int ft_print_info_file(t_content **entry, t_flags flags, int count)
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
    is_new_line = ft_print_files_in_args(entry, flags, columns);
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
            if (flags.R && current->subdir != NULL)
            {
                
                ft_recursive(current, flags);
                /* ft_printf("current->name: %s\n", current->name);
                t_content *r_subdir = current->subdir->begin;
                ft_printf("current->subdir->name: %s\n", r_subdir->name);
                
                ft_get_recursive_dir_content(&r_subdir, current->file_description->path, flags);
                //ft_printf("After recursive call\n");
                //ft_print_subdir(&r_subdir, flags);
                //ft_printf("After print info file inside R flag\n"); */
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