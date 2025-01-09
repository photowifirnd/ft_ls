/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-11 12:21:21 by jheras-f          #+#    #+#             */
/*   Updated: 2024-12-11 12:21:21 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

void execute_function(func_ptr_t func, int arg)
{
    if (func != NULL)
    {
        func(arg);
    }
}
int main(int args, char *argv[])
{
	t_content *container = NULL;
	t_flags flags;
	char **files_to_search = NULL;
	int file_count;
	int ret;

	file_count = 0;
	ret = 0;
 		
	ft_parse_ft_ls_argv(args, argv, &flags, &files_to_search, &file_count);
	ft_sortArray(files_to_search, file_count);
	
	if (file_count > 0)
		ret = ft_query_file(files_to_search, file_count, &container);
	t_content *current = ft_get_container_head(container);	
	if (current != NULL && current->name != NULL){
		
		while (current != NULL)
		{
			ft_query_dir(&current);
			current = current->next;
		}
	}
	ft_print_info_file(&container, flags);
	current = ft_get_container_head(container);
	while (current != NULL)
	{
		free_content_dir(&current->subdir);
		current = current->next;
	}
	
	free_content_dir(&container);
	for (int i = 0; i < file_count; i++)
		ft_free_alloc(files_to_search[i]);
	ft_free_alloc(files_to_search); 
	return (ret);
}