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
typedef struct		s_flags
{
	int				l;
	int				a;
	int				r;
	int				t;
	int				R;
}					t_flags;
typedef struct		s_user
{
	char			*name;
	char			*group;
	char			*perm;
	
	struct s_user	*next;
}					t_user;
typedef struct		s_file
{
	char			*name;
	char			*path;
	mode_t			perm;
	char			*user;
	char			*group;
	char			*size;
	char			*time;
	struct s_file	*next;
}					t_file;
typedef struct 	s_directory
{
    char	name[256];		// Nombre del archivo o directorio
	char	*path;			// Ruta del archivo o directorio
    off_t	size;			// Tamaño del archivo
    mode_t	permissions;	// Permisos del archivo
    uid_t	owner;			// ID del propietario
    gid_t	group;			// ID del grupo
    time_t	time;			// Fecha de modificación
    
} 				t_directory;

void ft_parse_ls_flags(int argc, char *argv[], t_flags *flags);
int ft_get_directory_entry(const char *path, t_directory *entry);

#endif