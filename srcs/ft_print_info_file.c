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
    ft_printf("%*d ", columns.nlink, file_description->nlink);
    ft_printf("%-*s ", columns.owner, file_description->str_owner);
    ft_printf("%-*s ", columns.group, file_description->str_group);
    ft_printf("%*d ", columns.size, file_description->size);
    
    ft_printf("%s ", date);
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
    t_content *current;
    t_content *tmp = NULL;
    t_content *new_node;

    int ret = 0;
    
    current = (flags.r) ? (*container)->end : (*container)->begin;
    while ( current != NULL)
    {
        if (current->file_description->type != 'd')
        {
            if (flags.is_flag && flags.l)
            {
                ft_print_description(current->file_description, columns);
            }
            else
            {
                new_node = new_container(current->file_description->fname);
                ft_add_new_node(&tmp, new_node); 
            }
            ret = 1;
        }
        current = (flags.r) ? current->prev : current->next;
    }
   
    
    if (tmp != NULL){
        current = tmp->begin;
        while (current != NULL)
        {
            ft_printf("%s", current->name);
            if (current->next != NULL)
            {
                ft_printf("  ");
            }
            current = current->next;
        }
        free_content_dir(&tmp);
    }
         current = (*container)->begin;
    
    while (current != NULL)
    {
        if (current->file_description->type != 'd')
        {
            //printf("\nremoving current->name: %s", current->name);
            current = ft_remove_node(current);
            if (current != NULL && current->file_description->type != 'd'){
                continue;
            }
            //printf("After removed current->name: %s", current->name);
            if (current == NULL){
                if (!flags.l)
                   ft_printf("\n");
                ret = -1;
                break;
            }
        }
        if (current->next == NULL){
            (*container) = current->begin;
        }
            
        current = current->next;
    }
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
int ft_print_info_file(t_content **entry, t_flags flags, int count, int is_recursive)
{
    (void)is_recursive;
    (void)count;
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
    if (is_new_line == -1){
        (*entry) = NULL;
        current = NULL;
    } else {
        current = (flags.r) ? (*entry)->end : (*entry)->begin;
    }
    /**
     * -1: entry became NULL
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
        if (current->error == -1 || (current->subdir != NULL && current->subdir->error == -1))
        {
            if (is_new_line == 1 && !flags.l)
            {
                    ft_printf("\n");
                    is_new_line = 0;
            }
            if (count > 1){
                ft_printf("%s:\n", current->file_description->fname);
            }
            if (flags.l)
                ft_printf("total %d\n", current->blk_total);
            ft_error_open_dir(current->name, 0);
            if (((!flags.r && current->next != NULL) || (flags.r && current->prev != NULL)))
                {
                    ft_printf("\n");
                    is_new_line = 0;
                }
            current = (flags.r) ? current->prev : current->next;
            continue;
        }
        // Handle the -l flag: Print detailed information
        if (flags.l || (flags.R && flags.l)) //This if is with -l flag
        {
            if (current->file_description->type == 'd')
            {
                if (count > 1 || flags.R){
                    ft_printf("%s:\n", current->file_description->fname);
                }
                ft_printf("total %d\n", current->blk_total);
                if (!current->blk_total && 
                   ((!flags.r && current->next != NULL) || (flags.r && current->prev != NULL)))
                {
                    ft_printf("\n");
                    is_new_line = 0;
                }
            }
            if (current->subdir != NULL)
            {
                ft_print_subdir(&current->subdir, flags);
                
                if (!is_recursive && !flags.R && ((!flags.r && current->next != NULL && current->next->file_description->type == 'd' && !is_new_line) ||
                    (flags.r && current->prev != NULL && current->prev->file_description->type == 'd' && !is_new_line)))
                {
                    ft_printf("\n");
                }
            }
            if (flags.R && current->subdir != NULL)
            {
                ft_recursive(current, flags);
                
                if (!is_recursive && !flags.a && !flags.r && current->next != NULL){
                    ft_printf("\n");
                    is_new_line = 0;
                }
                else if (!is_recursive && ((!flags.r && current->next != NULL && !no_directory) ||
                (flags.r && current->prev != NULL && !no_directory)))
                {
                    ft_printf("\n");
                }
                else if (!is_recursive && flags.r && !flags.a && current->prev != NULL && no_directory /* && current->prev->file_description->type == 'd' */) {
                    ft_printf("\n");
                }else if (!is_recursive && !flags.r && current->next != NULL && !is_new_line) {
                    ft_printf("\n");
                }
            }
        }
        else //From Here is without -l flag
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
                if (current->subdir == NULL && !is_recursive && ((!flags.r && current->next && current->prev->file_description->type == 'd') || (flags.r && current->prev && current->prev->file_description->type == 'd')))
                {
                    ft_printf("\n");
                }
            }
            if (current->subdir == NULL && !is_recursive  && !is_new_line &&
               ((!flags.r && current->next != NULL && current->next->file_description->type == 'd') ||
               (flags.r && current->prev != NULL && current->prev->file_description->type == 'd')))
            {
                ft_printf("\n");
            }
            if (current->subdir != NULL)
            {
                t_content *subdir;

                subdir = (flags.r) ? current->subdir->end : current->subdir->begin;
                while (subdir != NULL){
                    ft_printf("%s", subdir->file_description->fname);
                    if ((subdir->next != NULL && !flags.r) || (subdir->prev != NULL && flags.r))
                    {
                        ft_printf("  ");
                    }
                    subdir = (flags.r) ? subdir->prev : subdir->next;
                   
                }
                ft_printf("\n");
                if (!flags.R && !is_recursive && 
                   ((!flags.r && current->next != NULL && current->next->file_description->type =='d') ||
                   (flags.r && current->prev != NULL && current->prev->file_description->type == 'd')))
                {
                    ft_printf("\n");
                }
            }
            if (flags.R && current->subdir != NULL)
            {
                
                if ((ft_recursive(current, flags)) == EXIT_FAILURE)
                {
                    ft_printf("Failed to query directory %s\n", current->name);
                    return (EXIT_FAILURE);
                }
                 if (!is_recursive && !flags.a && !flags.r &&current->next != NULL){
                    ft_printf("\n");
                    is_new_line = 0;
                }
                else if (!is_recursive && ((!flags.r && current->next != NULL && !no_directory) ||
                (flags.r && current->prev != NULL && !no_directory)))
                {
                    ft_printf("\n");
                }
                else if (!is_recursive && flags.r && !flags.a && current->prev != NULL && no_directory && current->prev->file_description->type == 'd') {
                    ft_printf("\n");
                }
                if (!is_recursive && flags.R && flags.a &&((!flags.r && current->next != NULL && no_directory&& current->next->file_description->type == 'd')||(flags.r && current->prev != NULL && no_directory && current->prev->file_description->type == 'd')))
                {
                    ft_printf("\n");
                }
            }
        }
        current = (flags.r) ? current->prev : current->next;
    }
    if (!no_directory && is_new_line == 1 && !flags.l)
    {
        ft_printf("\n");
    }
    return (SUCCESS);
}