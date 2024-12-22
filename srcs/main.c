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
#include "libft.h"
#include "ft_printf.h"

void print_permissions(struct stat fileStat) {
    printf("File Permissions: ");
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

void ft_parse_ft_ls_argv(int argc, char *argv[], t_flags *flags, char ***files, int *file_count)
{
	// Array para guardar archivos/directorios
	*files = malloc(argc * sizeof(char *));//here is a malloc which must be freed
	*file_count = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if (ft_strcmp(argv[i], "--list") == 0)
			{
				flags->l = 1;
			}
			else if (ft_strcmp(argv[i], "--all") == 0)
			{
				flags->a = 1;
			}
			else if (ft_strcmp(argv[i], "--reverse") == 0)
			{
				flags->r = 1;
			}
			else if (ft_strcmp(argv[i], "--recursive") == 0)
			{
				flags->R = 1;
			}
			else if (argv[i][1] == '-')
			{
				ft_printf("Error: Invalid option -- %s\n", argv[i]);
				exit(EXIT_FAILURE);
			}
			else
			{
				for (int j = 1; argv[i][j] != '\0'; j++)
				{
					switch (argv[i][j])
					{
						case 'l': flags->l = 1; break;
						case 'a': flags->a = 1; break;
						case 'r': flags->r = 1; break;
						case 'R': flags->R = 1; break;
						case 't': flags->t = 1; break;
						default: fprintf(stderr, "Error: Invalid option -%c\n", argv[i][j]);
						exit(EXIT_FAILURE);
					}
				}
			}
		}
		else
		{
			(*files)[*file_count] = malloc((ft_strlen(argv[i]) + 1) * sizeof(char));
			ft_strcpy((*files)[*file_count], argv[i]);
			(*file_count)++;
		}
	}
}



// Función para llenar el struct con información del archivo
int ft_get_directory_entry(const char *path, t_directory *entry) {
    struct stat file_stat;
    if (stat(path, &file_stat) == -1) {
        perror("stat");
        return -1;
    }

    ft_strncpy(entry->name, path, sizeof(entry->name) - 1);
    entry->size = file_stat.st_size;
    entry->permissions = file_stat.st_mode;
    entry->owner = file_stat.st_uid;
    entry->group = file_stat.st_gid;
    entry->time = file_stat.st_atime;

    return 0;
}
int main(int args, char *argv[])
{
	char **files = NULL;
	int file_count = 0;
	t_directory entry;
	t_flags flags;

	if (args == 1)
	{
		ft_get_directory_entry("./", &entry);
		return (EXIT_SUCCESS);
	}
	if (args > 1)
	{
		ft_parse_ft_ls_argv(args, argv, &flags, &files, &file_count);
		printf("Flags: %d %d %d %d %d\n", flags.l, flags.a, flags.r, flags.R, flags.t);
		printf("Number of argumetns: %d\n", args);
	}

	// Mostrar archivos y directorios
	ft_printf("Archivos/Directorios:\n");
	for (int i = 0; i < file_count; i++)
	{
		printf("%s\n", files[i]);
		free(files[i]);
		// Liberar memoria
	}
	free(files);
	// Liberar memoria



	if (ft_get_directory_entry(argv[1], &entry) == 0)
	{
		ft_printf("Nombre: %s\n", entry.name);
		ft_printf("Tamaño: %d bytes\n", entry.size);
		ft_printf("Permisos: %o\n", entry.permissions);
		ft_printf("Propietario: %d\n", entry.owner);
		ft_printf("Grupo: %d\n", entry.group);
		ft_printf("Último acceso: %s", ctime(&entry.time));
	} else 
	{
		ft_printf("Error obteniendo la información del archivo.\n");
	}
	return (EXIT_SUCCESS);
}