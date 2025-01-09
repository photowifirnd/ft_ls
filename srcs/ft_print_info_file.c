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

//Print the detailed information of a file when the -l flag is set
void ft_print_description(t_file *file_description)
{
    char *date;
    
    date = ft_strtrim(file_description->date, "\n");
    ft_printf("%s ", file_description->str_perm);
    ft_printf("%d ", file_description->nlink);
    ft_printf("%s ", file_description->str_owner);
    ft_printf("%s ", file_description->str_group);
    ft_printf("%*d ", size_len, file_description->size);
    ft_printf("%s ", date);
    ft_printf("%s\n", file_description->fname);
    ft_free_alloc(date);
}
//print files in the container, not directories: intended for files passed as arguments
void ft_print_files_in_args(t_content **container, t_flags flags)
{
    t_content *current = *container;
    
    while ( current != NULL)
    {
        if (current->file_description->type != 'd')
        {
            if (!flags.is_flag)
            {
                ft_printf("%s ", current->file_description->fname);
            }
            else if (flags.is_flag && flags.l)
            {
                ft_print_description(current->file_description);
            }
        }
        current = current->next;
    }
}
//print files and directories in the given container: Intended for listing subdir content
void ft_print_subdir(t_content **subdir)
{
    t_content *current = *subdir;
    while (current != NULL)
    {
        ft_print_description(current->file_description);
        current = current->next;
    }
}
int ft_print_info_file(t_content **entry, t_flags flags)
{
    t_content *current;
    t_file *file_description;
    char *width_len;
    
    width_len = ft_itoa(size_len);
    size_len = ft_strlen(width_len);
    ft_free_alloc(width_len);
    
    if (entry == NULL || *entry == NULL){
        return (SUCCESS);
	}
    current = (*entry)->begin;
    ft_print_files_in_args(entry, flags);
    ft_printf("\n");
    current = (*entry)->begin;

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
            if (current->file_description->type == 'd')
            {
                ft_printf("\n%s:\n", current->file_description->fname);
                ft_printf("total: %d\n", current->blk_total);
            }
            ft_print_subdir(&current->subdir);
        }
        else
        {
            if (current->subdir != NULL)
            {
                ft_printf("\n%s:\n",current->file_description->fname);
                t_content *subdir = current->subdir->begin;
                while (subdir != NULL){
                   
                    ft_printf("%s ", subdir->file_description->fname);
                    subdir = subdir->next;
                }
                ft_printf("\n");
            }
        }
        current = current->next;
    }
    return (SUCCESS);
}