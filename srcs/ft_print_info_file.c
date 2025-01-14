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
    t_content *current = (*container);

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
void ft_print_files_in_args(t_content **container, t_flags flags, t_columns columns)
{
    t_content *current = *container;
    
    current = (flags.r) ? current->end : current->begin;
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
                ft_printf("%s ", current->file_description->fname);
            }
        }
        current = (flags.r) ? current->prev : current->next;
    }
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
int ft_print_info_file(t_content **entry, t_flags flags)
{
    t_content *current;
    //t_file *file_description;
    t_columns columns;

    ft_calculate_widths(&columns, entry);
    if (entry == NULL || *entry == NULL){
        return (SUCCESS);
	}
    current = (*entry)->begin;
    ft_print_files_in_args(entry, flags, columns);
    if ((*entry)->next != NULL)
    {
        ft_printf("\n");
    }
    current = (*entry)->begin;

    while (current != NULL)
    {
        /* file_description = current->file_description;

        // Handle the -a flag: Skip hidden files if -a is not set
        if (!flags.a && file_description->fname[0] == '.' && ft_strlen(file_description->fname) > 1)
        {
            current = current->next;
            continue;
        } */
        // Handle the -l flag: Print detailed information
        if (flags.l)
        {
            if (current->file_description->type == 'd')
            {
                ft_printf("\n%s:\n", current->file_description->fname);
                ft_printf("total: %d\n", current->blk_total);
            }
            if (current->subdir != NULL)
            {
                ft_print_subdir(&current->subdir, flags);
            }
        }
        else
        {
            if (current->subdir != NULL)
            {
                t_content *subdir;
                ft_printf("\n%s:\n",current->file_description->fname);
                subdir = (flags.r) ? current->subdir->end : current->subdir->begin;
                while (subdir != NULL){
                    if (subdir->name[0] == '.' && !flags.a)
                    {
                        subdir = (flags.r) ? subdir->prev : subdir->next;
                        continue;
                    }
                    ft_printf("%s ", subdir->file_description->fname);
                    subdir = (flags.r) ? subdir->prev : subdir->next;
                }
                ft_printf("\n");
            }
        }
        current = current->next;
    }
    return (SUCCESS);
}