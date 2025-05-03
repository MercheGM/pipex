/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:31 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/03 13:28:08 by mergarci         ###   ########.fr       */
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

# define READ 0 
# define WRITE 1 

//main.c
//main function

//pipes.c
int		ft_child(int *fd, char *command, char *infile, char **envp);
int		ft_parent(int *fd, char *command, char *outfile, char **envp);
void	ft_print_help(void);

//inputs.c
int		check_command(char *command, char **envp);

//split.c
char	**ft_split_bash(char *str);

#endif