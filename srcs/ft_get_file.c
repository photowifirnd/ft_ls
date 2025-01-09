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


off_t size_len = 0;
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
 * @brief Function to print deny access to a file
 */
int ft_deny_access(const char *path) {
    
    write(2, "ft_ls: cannot open directory ", 29);
    write(2, path, ft_strlen(path));
    write(2, ": Permission denied\n", 21);
    return 2;
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
    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);
    ft_strcpy(entry->file_description->str_owner, pwd->pw_name);
    ft_strcpy(entry->file_description->str_group, grp->gr_name);
}
/**
 * @brief Function to set the file description
 */
int ft_set_sub_file_description(const char *path, struct stat file_stat, t_content **container) {
    t_content *current_node = (*container);

    if (!(*container))
        return 2;
    
    if (!(current_node->file_description = (t_file *)ft_calloc(1, sizeof(t_file))))
        return 2;
    ft_bzero(current_node->file_description->fname, MAX_NAME);
    ft_bzero(current_node->file_description->path, MAX_PATH);
    ft_bzero(current_node->file_description->link, MAX_NAME);
    ft_strncpy(current_node->file_description->fname, current_node->name, sizeof(current_node->name) - 1);
    ft_set_str_permissions(file_stat.st_mode, current_node->file_description->str_perm);
    ft_bzero(current_node->file_description->path, MAX_NAME);
    ft_strcpy(current_node->file_description->path, path);
    current_node->file_description->inode = file_stat.st_ino;
    readlink(path, current_node->file_description->link, MAX_NAME);
    current_node->file_description->nlink = file_stat.st_nlink;
    current_node->file_description->size = file_stat.st_size;
    size_len = (size_len < current_node->file_description->size) ? current_node->file_description->size : size_len;
    current_node->file_description->permissions = file_stat.st_mode;
    current_node->file_description->owner = file_stat.st_uid;
    current_node->file_description->group = file_stat.st_gid;
    current_node->file_description->timestamp = file_stat.st_atime;
    current_node->file_description->date = ctime(&file_stat.st_atime);
    current_node->file_description->blocks = file_stat.st_blocks;
    current_node->file_description->block_size = file_stat.st_blksize;
    ft_set_ids(file_stat, current_node);
    ft_set_type(file_stat, current_node);

    // Debug prints
    /* ft_printf("Current node: %s\n", current_node->name);
    ft_printf("File description set for %s\n", current_node->file_description->fname);
    ft_printf("Permissions: %s\n", current_node->file_description->str_perm);
    ft_printf("Owner: %s\n", current_node->file_description->str_owner);
    ft_printf("Group: %s\n", current_node->file_description->str_group);
    ft_printf("Size: %lld\n", current_node->file_description->size);
    ft_printf("Date: %s\n", current_node->file_description->date); */
    return 0;
}
/**
 * @brief Function to set the file description
 */
int ft_set_file_description(const char *path, struct stat file_stat, t_content **container) {
    t_content *current_node;

    if (!(*container))
        return 2;
    current_node = ((*container)->end);
    if (!(current_node->file_description = (t_file *)ft_calloc(1, sizeof(t_file))))
        return 2;
    ft_strncpy(current_node->file_description->fname, current_node->name, sizeof(current_node->name) - 1);
    ft_set_str_permissions(file_stat.st_mode, current_node->file_description->str_perm);
    ft_bzero(current_node->file_description->path, MAX_NAME);
    ft_strcpy(current_node->file_description->path, path);
    current_node->file_description->nlink = file_stat.st_nlink;
    current_node->file_description->size = file_stat.st_size;
    size_len = (size_len < current_node->file_description->size) ? current_node->file_description->size : size_len;
    current_node->file_description->permissions = file_stat.st_mode;
    current_node->file_description->owner = file_stat.st_uid;
    current_node->file_description->group = file_stat.st_gid;
    current_node->file_description->timestamp = file_stat.st_atime;
    current_node->file_description->date = ctime(&file_stat.st_atime);
    current_node->file_description->blocks = file_stat.st_blocks;
    current_node->file_description->block_size = file_stat.st_blksize;
    ft_set_ids(file_stat, current_node);
    ft_set_type(file_stat, current_node);

    // Debug prints
    /* ft_printf("Current node: %s\n", current_node->name);
    ft_printf("File description set for %s\n", current_node->file_description->fname);
    ft_printf("Permissions: %s\n", current_node->file_description->str_perm);
    ft_printf("Owner: %s\n", current_node->file_description->str_owner);
    ft_printf("Group: %s\n", current_node->file_description->str_group);
    ft_printf("Size: %lld\n", current_node->file_description->size);
    ft_printf("Date: %s\n", current_node->file_description->date); */
    return 0;
}
/**
 * @brief Function to get full path of a file
 */
void ft_get_full_path(char *full_path, const char *path, const char *name)
{
    if (ft_strcmp(path, ".") == 0){
        ft_strcpy(full_path, path);
        ft_strcat(full_path, "/");
    }else{
        ft_strcpy(full_path, path);
    }
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
    
    if (file_stat.st_mode == 0 || ft_set_sub_file_description(path, file_stat, container) != 0) {
        ft_printf("Failed to set file description for %s\n", (*container)->file_description->path);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Function to fill the content of a directory
 */
int ft_fill_content_dir(t_content **content_dir, const char *path)
{
    DIR *dir;
    struct dirent *sdir;
    t_content *current = (*content_dir);
    
    if (!(dir = opendir(path))) {
        return ft_deny_access(path);
    }
    while ((sdir = readdir(dir)) != NULL)
    {
        // Skip the current and parent directory entries
        if (ft_strcmp(sdir->d_name, ".") == 0 || ft_strcmp(sdir->d_name, "..") == 0)
            continue;
        // Add the directory entry name to the content list
        if (insert_subdir_node(&current->subdir, sdir->d_name) == EXIT_FAILURE) {//CHECK if fails return to add_new_node
            ft_printf("Failed to add new node for %s\n", sdir->d_name);
            closedir(dir);
            return EXIT_FAILURE;
        }
    }
    closedir(dir);
    return EXIT_SUCCESS;
}
/**
 * @brief Function to query a file
 */
int ft_query_file(char **search, int search_count, t_content **container)
{
	int i = 0;
    while (i < search_count)
    {
        struct stat file_stat;
        
        if (lstat(search[i], &file_stat) == -1) {
            ft_deny_access(search[i]); //catch error to global var and return it at the exit program
        } else {
            if (add_new_node(container, search[i]) == EXIT_FAILURE) {
                ft_printf("Failed to add new node for %s\n", search[i]);
                return EXIT_FAILURE;
            }
            if (ft_set_file_description(search[i], file_stat, container) != 0) {
                ft_printf("Failed to set file description for %s\n", search[i]);
                return EXIT_FAILURE;
            }
        }
        
        i++;
    }
    /* ft_printf("*******************\n");
    t_content *current = (*container)->begin;
    while (current != NULL)
    {
        ft_printf("Current node: %s\n", current->name);
        ft_printf("File description set for %s\n", current->file_description->fname);
        ft_printf("Permissions: %s\n", current->file_description->str_perm);
        ft_printf("Owner: %s\n", current->file_description->str_owner);
        ft_printf("Group: %s\n", current->file_description->str_group);
        ft_printf("Size: %lld\n", current->file_description->size);
        ft_printf("Date: %s\n", current->file_description->date);
        current = current->next;
    }
    ft_printf("*******************\n"); */
    //ft_printf("Size we must use to format size of file: %d\n", size_len);
    return (EXIT_SUCCESS);
}
/**
 * @brief Function to query a directory
 */
int ft_query_dir(t_content **container){
    char full_path[4096];
    t_content *subdir;
    t_content *current = (*container);

    ft_bzero(full_path, 4096);
    if (current->file_description->type == 'd')
    {
        if (ft_fill_content_dir(&current, current->file_description->fname) != EXIT_SUCCESS)
        {
            return EXIT_FAILURE;
        }
        subdir = (*container)->begin->subdir->begin;
        while (subdir != NULL)
        {
            ft_get_full_path(full_path, (*container)->name, subdir->name);
            ft_fill_description(full_path, &subdir);
            current->blk_total += subdir->file_description->blocks;
            subdir = subdir->next;
        } 
    }
    return EXIT_SUCCESS;
}