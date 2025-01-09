#include "ft_ls.h"

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

    while (current_node != NULL && ft_strcmp(current_node->name, name) < 0)
    {
        current_node = current_node->next;
    }
	//ft_printf("begining node %s\n", (*subdir)->name);
	//ft_printf("Current node %s - Inserting %s\n", current_node->name, name);
	if (!(new_node = new_container()))
			return (EXIT_FAILURE);
	ft_strcpy(new_node->name, name);
	if (current_node == NULL) //Insert at the end
	{
		ft_printf("Inserting at the end\n");
		/*current_node->next->prev = current_node;
        current_node = current_node->next;
        ft_strcpy(current_node->name, name);
        (*container)->end = current_node;*/

		t_content *last = (*subdir)->end;
		last->next = new_node;
        new_node->prev = last;
		new_node->end = new_node;
        new_node->begin = (*subdir)->begin;
        //new_node->end = new_node;
		
		current_node = (*subdir)->begin;
		while (current_node != NULL){
        	current_node->end = new_node;
			current_node = current_node->next;
		}
		
	}
	else if (current_node == *subdir) //Insert at the begining
	{
		ft_printf("Inserting at the begining\n");
		current_node->prev = new_node;
		current_node->begin = new_node;
		new_node->next = current_node;
		new_node->end = new_node->next->end;
		new_node->next->prev = new_node;
		new_node->next->begin = new_node;
		

		/* ft_printf("*******************\n");
		ft_printf("new_node %s\n", new_node->name);
		ft_printf("new_node->begin %s\n", new_node->begin->name);
		ft_printf("new_node->end %s\n", new_node->end->name);
		ft_printf("current_node->end %s\n", current_node->end->name);
		ft_printf("new_node->next %s\n", new_node->next->name);
		ft_printf("new_node->prev %s\n", new_node->prev->name);
		ft_printf("*****************\n"); */
		
		(*subdir) = new_node;
		current_node = (*subdir)->begin;
		while (current_node != NULL){
			//ft_printf("set begining of %s\n", current_node->name);
        	current_node->begin = new_node;
			current_node = current_node->next;
		}
	} 
	else
	{
		ft_printf("Inserting in the middle\n");
		new_node->end = (*subdir)->end;
		new_node->begin = (*subdir)->begin;
		new_node->next = current_node;
		new_node->prev = current_node->prev;
		current_node->prev = new_node;
       
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
