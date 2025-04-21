/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:31 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/19 22:04:33 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

# define READ_END 0 
# define WRITE_END 1 

# define READ 0 
# define WRITE 1 

//pipes_bonus.c
int		ft_first_child(int *fd, int *fd_next, char *command, char *infile, char **envp);
int		ft_middle_child(int *fd_new, int *fd_old, char *command, char **envp);
int		ft_parent(int *fd, char *command, char *outfile, char **envp);
void	ft_print_help(void);
int		ft_child_2(int *prev_pipe_fd, int *fd, int cont, char **argv, char **envp);
int	ft_count_string(char **string);
//inputs_bonus.c
int		check_command(char *command, char **envp);

#endif