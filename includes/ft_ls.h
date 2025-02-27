/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-16 11:08:56 by jheras-f          #+#    #+#             */
/*   Updated: 2024-12-16 11:08:56 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include "libft.h"
# include "ft_printf.h"
# include "constants.h"

extern int var_error;
typedef struct s_columns
{
	nlink_t		nlink;
	int		owner;
	int		group;
	off_t		size;
} t_columns;
typedef struct		s_flags
{
	int				l;
	int				a;
	int				r;
	int				t;
	int				R;
	int				is_flag;
}					t_flags;
typedef struct 	s_file
{
	char				type;			// Type of file
    char				fname[MAX_NAME];		// File name 256 max length
	char				path[MAX_PATH];			// Ruta del archivo o directorio 4096 max length
	nlink_t				nlink;			// número de links
	ino_t				inode;			// Número de inodo
	char				link[MAX_NAME];			// Enlace simbólico
    off_t				size;			// Tamaño del archivo
    mode_t				permissions;	// Permisos del archivo
	char				str_perm[11];		// Permisos en formato string
    uid_t				owner;			// ID del propietario
    gid_t				group;			// ID del grupo
	char				str_owner[MAX_NAME];			// usuario propietario
	char				str_group[MAX_NAME];			// grupo propietario
    time_t				timestamp;			// Fecha de modificación
	char*				date;
	blkcnt_t			blocks;			// Bloques asignados
	long				block_size;		// Tamaño de bloque
} 				t_file;
typedef struct	s_content
{
	char					name[MAX_PATH];
	int						error;
	int 					blk_total;
	struct s_file			*file_description;
	struct s_content		*subdir;
	struct s_content		*begin;
	struct s_content		*end;
	struct s_content		*next;
	struct s_content		*prev;
}				t_content;

/*Test purposes with pointer function*/
typedef void (*func_ptr_t)(int);
/*End Test*/

void ft_parse_ft_ls_argv(int argc, char *argv[], t_flags *flags, char ***files, int *file_count);
int ft_query_file(char **search, int search_count, t_content **content, t_flags flags);
int ft_query_dir(t_content **container, t_flags flags);
int ft_set_file_description(const char *path, struct stat file_stat , t_content *container);
void ft_set_str_permissions(mode_t st_mode, char *str_perm);
int ft_print_info_file(t_content **entry, t_flags flags, int count, int is_recursive);
void ft_print_subdir(t_content **subdir, t_flags flags);
int ft_open_directory(char *path, t_content *entry);
int ft_fill_content_dir(t_content **content_dir, const char *path, t_flags flags);
void ft_get_full_path(char *full_path, const char *path, const char *name);
int ft_fill_description(char *path, t_content **container);
void ft_calculate_widths(t_columns *columns, t_content **subdir);

t_content *new_container(const char *name);
t_content *ft_remove_node(t_content *node);
int ft_add_new_node(t_content **head, t_content *new_node);
int ft_add_new_node_alphanumeric(t_content **container, t_content *new_node);
int ft_add_new_node_by_time(t_content **container, t_content *node);
//int insert_subdir_node(t_content **subdir, const char *name);
t_content *ft_get_container_head(t_content *container);
void free_content_dir(t_content **container);

void ft_get_recursive_dir_content(t_content **container, const char *path, t_flags flags);
int ft_recursive(t_content *dir, t_flags flags);

//Print errors
void ft_invalid_option(char *str);
void ft_unrecognized_option(char *str);
int ft_deny_access(const char *path);
int ft_error_open_dir(const char *path, int is_new_line);

#endif