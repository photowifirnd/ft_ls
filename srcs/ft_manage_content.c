#include "ft_ls.h"

// Initialize a new t_content_dir structure
t_content *new_container(const char *name)
{
    t_content *new_node;

	if (!name || !ft_strlen(name))
	{
		return NULL;
	}
    if (!(new_node = (t_content *)malloc(sizeof(t_content))))
	{
        return NULL;
	}
    ft_bzero(new_node->name, MAX_NAME);
	ft_strcpy(new_node->name, name);
	new_node->error = 0;
	new_node->blk_total = 0;
    new_node->begin = new_node;
    new_node->end = new_node;
    new_node->subdir = NULL;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->file_description = NULL;
    return new_node;
}
int ft_delete_node(t_content *node_to_delete){
	node_to_delete->next = NULL;
	node_to_delete->prev = NULL;
	node_to_delete->begin = node_to_delete;
	node_to_delete->end = node_to_delete;
	if (node_to_delete->subdir != NULL){
		ft_printf("Removing subdir: %s\n", node_to_delete->name);
		free_content_dir(&node_to_delete->subdir);
	}
	free_content_dir(&node_to_delete);
	return EXIT_SUCCESS;
}
t_content *ft_remove_node(t_content *node)
{
	t_content *current;
	t_content *tmp;

	if (node == NULL)
		return NULL;
	current = node->begin;
	if (node->begin == node){
		//ft_printf("Removing from head: node_to_delete is the begining: %s\n", node->name);
		if (current->next == NULL){
			ft_delete_node(node);
			return NULL;
		}
		tmp = node->next;
		tmp->prev = NULL;
		tmp->begin = tmp;
		t_content *aux = tmp->begin;
		while (aux != NULL){
			aux->begin = tmp;
			aux = aux->next;
		}
		ft_delete_node(node);
		return tmp;
	} else if (node->end == node){
		//ft_printf("Removing from tail: node_to_delete is the end: %s\n", node->name);
		if (node->prev == NULL){
			ft_delete_node(node);
			return NULL;
		}
		tmp = node->prev;
		tmp->next = NULL;
		tmp->end = tmp;
		t_content *aux = tmp->begin;
		while (aux != NULL){
			aux->end = tmp;
			aux = aux->next;
		}
		ft_delete_node(node);
		return tmp;
	} else {
		
		while (current != NULL){
			if (current == node){
				//ft_printf("Removing from middle: node_to_delete is in the middle: %s\n", node->name);
				tmp = node->prev;
				tmp->next = node->next;
				node->next->prev = tmp;
				ft_delete_node(node);
				node = tmp;
				return node;
			}
			current = current->next;
		}
	}
	return EXIT_SUCCESS;
}
//function to insert at the begining of a container
int ft_insert_at_begining(t_content **container, t_content *new_node)
{
	t_content *current_node;
	if (!(*container))
	{
		*container = new_node;
	}
	else
	{
		current_node = (*container)->begin;
		new_node->next = current_node;
		new_node->end = new_node->next->end;
		new_node->next->prev = new_node;
		new_node->next->begin = new_node;
		*container = new_node;
		current_node = (*container)->begin;
		while (current_node != NULL){
			current_node->begin = new_node;
			current_node = current_node->next;
		}
	}
	
	return EXIT_SUCCESS;
}
//function to insert in the middle of a container before container position
int ft_insert_in_between(t_content **container, t_content *new_node)
{
	//print debug container
	/* ft_printf("Inserting in the middle %s\n", new_node->name);
	ft_printf("*****************\n");
	ft_printf("Container: \n");
	ft_printf("Begin: %s\n", (*container)->begin->name);
	ft_printf("current: %s\n", (*container)->name);
	ft_printf("Next: %s\n", (*container)->next->name);
	ft_printf("Prev: %s\n", (*container)->prev->name);
	ft_printf("End: %s\n", (*container)->end->name);
	ft_printf("*****************\n"); */
	//end debug

	t_content *current_node;
	if (!(*container))
	{
		*container = new_node;
	}
	else
	{
		current_node = (*container);
		new_node->next = current_node;
		new_node->prev = current_node->prev;
		if (current_node->prev)
                current_node->prev->next = new_node;
		new_node->prev->next = new_node;
		current_node->prev = new_node;
		new_node->begin = (*container)->begin;
	}
	return EXIT_SUCCESS;
}
//function to insert at the end of a container
int ft_insert_at_ending(t_content **container, t_content *new_node)
{
	t_content *current_node;

	if (!(*container))
	{
		*container = new_node;
	}
	else
	{
		current_node = (*container)->end;
		new_node->begin = current_node->begin;
		current_node->next = new_node;
		current_node->next->prev = current_node;
		current_node->end = new_node;

		current_node = (*container)->begin;
		while (current_node != NULL){
			current_node->end = new_node;
			current_node = current_node->next;
		}
	}
	return EXIT_SUCCESS;
}
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
//get the end of the container
t_content *ft_get_container_tail(t_content *container)
{
	return container->end;
}
// Add a new entry to the t_content_dir list
int ft_add_new_node(t_content **container, t_content *new_node/* , const char *name */)
{
    t_content *current_node;
    
    if (!(*container))
    {
        *container = new_node;
    }
	else
	{
		current_node = (*container)->end;
		current_node->next = new_node;
		new_node->prev = current_node;
		current_node = (*container)->begin;
		while (current_node != NULL){
			current_node->end = new_node;
			current_node = current_node->next;
		}
    }
   return EXIT_SUCCESS;
}
int ft_add_new_node_alphanumeric(t_content **container, t_content *new_node)
{
	if ((*container) == NULL){
		*container = new_node;
		return EXIT_SUCCESS;
	}
	t_content *current = (*container)->begin;
	while (current != NULL){
		if (ft_strcmp(current->name, new_node->name) > 0)
		{
			if (current->prev == NULL){ 
				return ft_insert_at_begining(&current, new_node);
			} else {
				return ft_insert_in_between(&current, new_node);
			}
		}
		if (current->next == NULL){
			return ft_insert_at_ending(&current, new_node);
		}
		current = current->next;
	}
	return EXIT_SUCCESS;
}
int ft_add_new_node_by_time(t_content **container, t_content *new_node)
{
	if ((*container) == NULL){
		*container = new_node;
		return EXIT_SUCCESS;
	}
	t_content *current = (*container)->begin;
	while (current != NULL){
		if (current->file_description->timestamp < new_node->file_description->timestamp)
		{
			if (current->prev == NULL){ 
				return ft_insert_at_begining(&current, new_node);
			} else {
				return ft_insert_in_between(&current, new_node);
			}
		}
		else if (current->file_description->timestamp == new_node->file_description->timestamp)
		{
			if (ft_strcmp(current->name, new_node->name) >= 0)//("a", "b")
			{
				if (current->prev == NULL) {
					return ft_insert_at_begining(&current, new_node);
				}
				else {
					return ft_insert_in_between(&current, new_node);
				}
			}
		}
		if (current->next == NULL){
			return ft_insert_at_ending(&current, new_node);
		}
		current = current->next;
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
			ft_free_alloc(current->file_description->date);
            ft_free_alloc(current->file_description);
        }
        next = current->next;
        ft_free_alloc(current);
        current = next;
    }
}
/**************************************************************** */
/* // Insert a new node maintaining the alfanumeric order
int insert_subdir_node(t_content **subdir, const char *name)
{
    t_content *current_node;
    t_content *new_node;
    if (!name || !ft_strlen(name))
        return EXIT_FAILURE;
    if (!(*subdir))
    {
		if (!(*subdir = new_container(name)))
		    return (EXIT_FAILURE);
		return EXIT_SUCCESS;
    }
	//ft_printf("Inserting new subdir %s\n", name);
    current_node = (*subdir)->begin;
    while (current_node != NULL && ft_strcmp(current_node->name, name) < 0)
    {
        current_node = current_node->next;
    }
	if (!(new_node = new_container(name)))
			return (EXIT_FAILURE);
	if (current_node == NULL) //Insert at the end
	{
		//ft_printf("Inserting at the end\n");
		ft_insert_at_ending(subdir, new_node);
	}
	else if (current_node == *subdir) //Insert at the begining
	{
		//ft_printf("Inserting at the begining -> %s\n", name);
		ft_insert_at_begining(subdir, new_node);
	} 
	else //before current_node Insrtion in the middle
	{
		ft_insert_in_between(&current_node, new_node);
	}
	return EXIT_SUCCESS;
}
 */