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
int var_error = 0;

int main(int args, char *argv[])
{
	t_content *container = NULL;
	t_flags flags;
	char **files_to_search = NULL;
	int file_count;
	
	file_count = 0;
	 		
	ft_parse_ft_ls_argv(args, argv, &flags, &files_to_search, &file_count);
	ft_sortArray(files_to_search, file_count);
	
	if (file_count > 0)
		var_error = ft_query_file(files_to_search, file_count, &container, flags);
	//we have to check for container and make sure it is not null. Have in mindo all mallocs and frees
	if (container != NULL)
	{
		t_content *current = ft_get_container_head(container);
		
		if (current != NULL && current->name != NULL){
			
			while (current != NULL)
			{
				
				if ((ft_query_dir(&current, flags)) == EXIT_FAILURE)
				{
					ft_printf("Failed to query directory %s\n", current->name);
					return (EXIT_FAILURE);
				}
				current = current->next;
			}
		}
		if ((ft_print_info_file(&container, flags, file_count, 0)) == EXIT_FAILURE)
		{
			ft_printf("Failed to print info file\n");
			return (EXIT_FAILURE);
		}
		//ft_recursive(&(*container), flags);
		current = ft_get_container_head(container);
		while (current != NULL)
		{
			free_content_dir(&current->subdir);
			current = current->next;
		}
		
		free_content_dir(&container);
	}
	for (int i = 0; i < file_count; i++)
		ft_free_alloc(files_to_search[i]);
	ft_free_alloc(files_to_search); 
	return (var_error);
}