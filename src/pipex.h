/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:31 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/28 20:22:42 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/ft_printf.h"
# include <unistd.h>
# include <stdio.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//inputs.c
char  **check_argv(int argc, char *argv[]);
char *check_command(char *command);

//utils.c
char *free_memory(char *ptr);

#endif