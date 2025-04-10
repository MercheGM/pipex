/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:31 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/09 20:49:02 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# define READ 0 /*extremo lectura*/
# define WRITE 1 /*extremo escritura*/

//inputs.c
char	**check_argv(int argc, char *argv[]);
int		check_command(char *command, char **envp);

//utils.c
//char *free_memory(char *ptr);

#endif