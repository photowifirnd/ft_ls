/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-23 07:08:54 by jheras-f          #+#    #+#             */
/*   Updated: 2024-12-23 07:08:54 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief Function to set date of a file if file is lower than 6 months old or greater than 6 months old
 */
char *ft_set_date(time_t timestamp)
{
    time_t current_time;
    time_t file_time;
    time_t diff_time;
    time_t six_months = 15778463; // Approximately six months in seconds
    char date[20]; // Buffer to hold the formatted date
    
    ft_bzero(date, 20);
    current_time = time(NULL);
    file_time = timestamp;
    diff_time = current_time - file_time;

    // Format the date based on the difference in time
    if (diff_time < six_months)
    {
        // Format the date as "Month Day Hour:Minute"
        ft_strcpy(date, ctime(&file_time) + 4);
        date[12] = '\0';
    }
    else
    {
        // Format the date as "Month Day  Year"
        ft_strncpy(date, ctime(&file_time) + 4, 7);
        ft_strncpy(date + 7, ctime(&file_time) + 19, 5);
        date[12] = '\0';
    }

    return ft_strdup(date);
}

/**
 * @brief Function to set the permissions of a file
 */
void ft_set_str_permissions(mode_t st_mode, char *str_perm) {
    ft_bzero(str_perm, 11);
	str_perm[0] = (S_ISDIR(st_mode)) ? 'd' : '-';
    str_perm[1] = (st_mode & S_IRUSR) ? 'r' : '-';
    str_perm[2] = (st_mode & S_IWUSR) ? 'w' : '-';
    str_perm[3] = (st_mode & S_IXUSR) ? 'x' : '-';
    str_perm[4] = (st_mode & S_IRGRP) ? 'r' : '-';
    str_perm[5] = (st_mode & S_IWGRP) ? 'w' : '-';
    str_perm[6] = (st_mode & S_IXGRP) ? 'x' : '-';
    str_perm[7] = (st_mode & S_IROTH) ? 'r' : '-';
    str_perm[8] = (st_mode & S_IWOTH) ? 'w' : '-';
    str_perm[9] = (st_mode & S_IXOTH) ? 'x' : '-';
}
/**
 * @brief Function to set the type of a file
 */
void ft_set_type(struct stat file_stat, t_content *entry) {
    if (S_ISDIR(file_stat.st_mode))
        entry->file_description->type = 'd';
    else if (S_ISLNK(file_stat.st_mode))
        entry->file_description->type = 'l';
    else if (S_ISCHR(file_stat.st_mode))
        entry->file_description->type = 'c';
    else if (S_ISBLK(file_stat.st_mode))
        entry->file_description->type = 'b';
    else if (S_ISFIFO(file_stat.st_mode))
        entry->file_description->type = 'p';
    else if (S_ISSOCK(file_stat.st_mode))
        entry->file_description->type = 's';
    else
    {
        entry->file_description->type = '-';
    }
    entry->file_description->str_perm[0] = entry->file_description->type;
}
/**
 * @brief Function to set the owner and group of a file
 */
void ft_set_ids(struct stat file_stat, t_content *entry) {
    char *owner = NULL;
    char *group = NULL;
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);

    if (pwd == NULL)
    {
        owner = ft_itoa(file_stat.st_uid);
        ft_strcpy(entry->file_description->str_owner, owner);
        ft_free_alloc(owner);
    }
    else
    {
        ft_strcpy(entry->file_description->str_owner, pwd->pw_name);
    }
    if (grp == NULL)
    {
        group = ft_itoa(file_stat.st_gid);
        ft_strcpy(entry->file_description->str_group, group);
        ft_free_alloc(group);
    }
    else
    {
        ft_strcpy(entry->file_description->str_group, grp->gr_name);
    }
}
/**
 * @brief Function to set the file description
 */
int ft_set_file_description(const char *path, struct stat file_stat, t_content *container) {
    t_content *current_node;
    if (!(container))
        return 2;
    current_node = ((container)->end); // Why is this have to be the end of the list?
    if (!(current_node->file_description = (t_file *)ft_calloc(1, sizeof(t_file))))
        return 2;
    ft_bzero(current_node->file_description->fname, MAX_NAME);
    ft_bzero(current_node->file_description->link, MAX_NAME);
    ft_bzero(current_node->file_description->path, MAX_PATH);
    ft_strcpy(current_node->file_description->fname, current_node->name);
    ft_strcpy(current_node->file_description->path, path);
    ft_set_str_permissions(file_stat.st_mode, current_node->file_description->str_perm);
    current_node->file_description->nlink = file_stat.st_nlink;
    current_node->file_description->inode = file_stat.st_ino;
    readlink(path, current_node->file_description->link, MAX_NAME);
    current_node->file_description->size = file_stat.st_size;
    current_node->file_description->permissions = file_stat.st_mode;
    current_node->file_description->owner = file_stat.st_uid;
    current_node->file_description->group = file_stat.st_gid;
    current_node->file_description->timestamp = file_stat.st_mtime;
    current_node->file_description->date = ft_set_date(current_node->file_description->timestamp);
    current_node->file_description->blocks = file_stat.st_blocks;
    current_node->file_description->block_size = file_stat.st_blksize;
    ft_set_ids(file_stat, current_node);
    ft_set_type(file_stat, current_node);
    return EXIT_SUCCESS;
}
/**
 * @brief Function to get full path of a file
 */
void ft_get_full_path(char *full_path, const char *path, const char *name)
{
    if (path && path[ft_strlen(path) - 1] != '/')
    {
        ft_strcpy(full_path, path);
        ft_strcat(full_path, "/");
        if (name && ft_strlen(name) > 0){
            ft_strcat(full_path, name);
        }
        return ;
    }
    ft_strcpy(full_path, path);
    ft_strcat(full_path, name);
}
/**
 * @brief Function to get files lstat 
 */
struct stat ft_get_file_stat(char *file_path)
{
    struct stat file_stat = {0};
        
    if (lstat(file_path, &file_stat) == -1)
    {
        ft_deny_access(file_path);
    }
    return file_stat;
}
/**
 * @brief Function to add a new node to the container
 */
int ft_fill_description(char *path, t_content **container)
{
    struct stat file_stat = ft_get_file_stat(path);
    
    if (file_stat.st_mode == 0 || ft_set_file_description(path, file_stat, (*container)) != 0) {
        ft_printf("Failed to set file description for %s\n", path);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Function to fill the content of a directory
 */
int ft_fill_content_dir(t_content **content_dir, const char *path, t_flags flags)
{
    char full_path[MAX_PATH];
    DIR *dir;
    struct dirent *sdir;
    t_content *current = (*content_dir);
    t_content *new_node;
    
    if (!(dir = opendir(path))) {
        new_node = new_container(path);
        new_node->error = -1;
        ft_add_new_node(&current->subdir, new_node);
        return 2;
    }
    while ((sdir = readdir(dir)) != NULL)
    {
        // Skip the current and parent directory entries
        if (flags.a == 0 && sdir->d_name[0] == '.')
            continue;
        ft_get_full_path(full_path, (*content_dir)->name, sdir->d_name);
        new_node = new_container(sdir->d_name);
        if ((ft_fill_description(full_path, &new_node)) != EXIT_SUCCESS)
        {
            ft_printf("Failed to set file description for %s\n", sdir->d_name);
            continue;
            //return EXIT_FAILURE; // Or should continue?
        }
        current->blk_total += new_node->file_description->blocks;
        // Add the directory entry name to the content list
        if (flags.t){
            if (ft_add_new_node_by_time(&current->subdir, new_node) == EXIT_FAILURE)
            {
                ft_printf("Failed to add new node for %s\n", sdir->d_name);
                continue;
                //closedir(dir);
                //return EXIT_FAILURE; // Or should continue?
            }
        }
        else
        {
            if (ft_add_new_node_alphanumeric(&current->subdir, new_node) == EXIT_FAILURE)
            {
                ft_printf("Failed to add new node for %s\n", sdir->d_name);
                continue;
                //closedir(dir);
                //return EXIT_FAILURE; // Or should continue?
            } 
        }
    }
    closedir(dir);
    return EXIT_SUCCESS;
}
/**
 * @brief Function to query a file
 */
int ft_query_file(char **search, int search_count, t_content **container, t_flags flags)
{
    t_content *new_node;
	int i = 0;
   
    while (i < search_count)
    {
        struct stat file_stat;
        if (lstat(search[i], &file_stat) == -1) {
            var_error = ft_deny_access(search[i]);
        } else {
            new_node = new_container(search[i]);
            if (ft_set_file_description(search[i], file_stat,  new_node) != 0) {
                ft_printf("Failed to set file description for %s\n", search[i]);
                return EXIT_FAILURE;
            }
            if (flags.t == 0)
            {
                if (ft_add_new_node_alphanumeric(container, new_node) == EXIT_FAILURE) {
                    ft_printf("Failed to add new node for %s\n", search[i]);
                    return EXIT_FAILURE;
                }
            }
            else
            {
                if (ft_add_new_node_by_time(container, new_node) == EXIT_FAILURE) {
                    ft_printf("Failed to add new node for %s\n", search[i]);
                    return EXIT_FAILURE;
                }
            }
        }
        i++;
    }
    return (var_error);
}
/**
 * @brief Function to query a directory
 */
int ft_query_dir(t_content **container, t_flags flags){
    t_content *current = (*container);

    if (current->file_description->type == 'd')
    {
        return ft_fill_content_dir(&current, current->file_description->path, flags);
    }
    return EXIT_SUCCESS;
}