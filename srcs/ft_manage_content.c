#include "ft_ls.h"
//Checks if file is already in the container
int ft_check_file(t_content **container, const char *name)
{
	t_content *current_node;
	if (!name || !ft_strlen(name))
		return EXIT_FAILURE;
	if (!(*container))
	{
		return EXIT_FAILURE;
	} else {
		current_node = (*container)->begin;
		while (current_node != NULL)
		{
			if (ft_strcmp(current_node->name, name) == 0)
			{
				return EXIT_SUCCESS;
			}
			current_node = current_node->next;
		}
	}
	return EXIT_FAILURE;
}
//get the head of the container
t_content *ft_get_container_head(t_content *container)
{
    return container->begin;
}
// Initialize a new t_content_dir structure
t_content *new_container(void)
{
    t_content *new_node;
    if (!(new_node = (t_content *)malloc(sizeof(t_content))))
        return NULL;
    
    ft_bzero(new_node->name, MAX_NAME);
	new_node->blk_total = 0;
    new_node->begin = new_node;
    new_node->end = new_node;
    new_node->subdir = NULL;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->file_description = NULL;
    return new_node;
}

// Add a new entry to the t_content_dir list
int add_new_node(t_content **container, const char *name)
{
    t_content *current_node;
    
    if (!name || !ft_strlen(name))
        return EXIT_FAILURE;
    if (!(*container))
    {
        if (!(*container = new_container()))
		    return (EXIT_FAILURE);
        ft_strcpy((*container)->name, name);
    } else {
		if (ft_check_file(container, name) == 0)
		{
			return EXIT_SUCCESS;
		}
        current_node = (*container)->end;///Here seems to be the problem when passing subdirs. CHECK THIS!!!
        if (!(current_node->next = new_container()))
            return (EXIT_FAILURE);
        current_node->next->prev = current_node;
        current_node = current_node->next;
        ft_strcpy(current_node->name, name);
        (*container)->end = current_node;
    }
   return EXIT_SUCCESS;
}
// Insert a new node maintaining the alfanumeric order
int insert_subdir_node(t_content **subdir, const char *name)
{
    t_content *current_node;
    t_content *new_node;
    if (!name || !ft_strlen(name))
        return EXIT_FAILURE;
    if (!(*subdir))
    {
		if (!(*subdir = new_container()))
		    return (EXIT_FAILURE);
        ft_strcpy((*subdir)->name, name);
		return EXIT_SUCCESS;
    }
	//ft_printf("Inserting new subdir %s\n", name);
    current_node = (*subdir)->begin;
	if (ft_check_file(subdir, name) == 0)
	{
		return EXIT_SUCCESS;
	}
    while (current_node != NULL && ft_strcmp(current_node->name, name) < 0)
    {
        current_node = current_node->next;
    }
	if (!(new_node = new_container()))
			return (EXIT_FAILURE);
	ft_strcpy(new_node->name, name);
	if (current_node == NULL) //Insert at the end
	{
		//ft_printf("Inserting at the end\n");
		t_content *last = (*subdir)->end;
		last->next = new_node;
        new_node->prev = last;
		new_node->end = new_node;
        new_node->begin = (*subdir)->begin;
		
		current_node = (*subdir)->begin;
		while (current_node != NULL){
        	current_node->end = new_node;
			current_node = current_node->next;
		}
		
	}
	else if (current_node == *subdir) //Insert at the begining
	{
		//ft_printf("Inserting at the begining\n");
		current_node->prev = new_node;
		current_node->begin = new_node;
		new_node->next = current_node;
		new_node->end = new_node->next->end;
		new_node->next->prev = new_node;
		new_node->next->begin = new_node;

		(*subdir) = new_node;
		current_node = (*subdir)->begin;
		while (current_node != NULL){
			//ft_printf("set begining of %s\n", current_node->name);
        	current_node->begin = new_node;
			current_node = current_node->next;
		}
	} 
	else //before current_node Insrtion in the middle
	{
		new_node->end = (*subdir)->end;
		new_node->begin = (*subdir)->begin;
		new_node->next = current_node;
		new_node->prev = current_node->prev;
		current_node->prev = new_node;
		new_node->prev->next = new_node;

		
	}
	
	return EXIT_SUCCESS;
}

// Free the t_content_dir list
void free_content_dir(t_content **container)
{
    if (!(*container))
        return;
    t_content *current = (*container)->begin;
    t_content *next;

    while (current != NULL)
    {
        if (current->file_description != NULL) {
            free(current->file_description);
        }
        next = current->next;
        free(current);
        current = next;
    }
}
