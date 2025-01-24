/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <jheras-f@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-24 12:21:46 by jheras-f          #+#    #+#             */
/*   Updated: 2025-01-24 12:21:46 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * @brief Function to print deny access to a file
 */
int ft_deny_access(const char *path)
{
    
    write(2, "ft_ls: cannot access '", 22);
    write(2, path, ft_strlen(path));
    write(2, "': No such file or directory\n", 29);
    var_error = ERROR; //Substitute this for a global variable Constant lile ACCESS_DENIED
    return var_error;
}
int ft_error_open_dir(const char *path, int is_new_line)
{
    (void)is_new_line;
    write(2, "ft_ls: cannot open directory '", 30);
    write(2, path, ft_strlen(path));
    write(2, "': Permission denied\n", 21);
    
    var_error = ERROR; //Substitute this for a global variable Constant lile ACCESS_DENIED
    return var_error;
}
void ft_invalid_option(char *str)
{
	//Change it for ft_putstrfd
	write(2, "ft_ls: invalid option -- '", 26);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	write(2, "Usage: ft_ls [-alrtR] [file ...]\n", 33);
	var_error = ERROR;
	return;
}
void ft_unrecognized_option(char *str)
{
	//Change it for ft_putstrfd
	write(2, "ft_ls: unrecognized option '", 28);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	write(2, "Usage: ft_ls [-alrtR] [file ...]\n", 33);
	var_error = ERROR;
	return;
}
void ft_print_error(char *err)
{
	ft_putstr_fd(err, 2);
	var_error = ERROR; //Substitute this for a global variable Constant lile ACCESS_DENIED
	return;
}