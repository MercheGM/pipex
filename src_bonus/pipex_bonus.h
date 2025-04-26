/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:31 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/26 13:42:59 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/ft_printf.h"
# include "../libft/gnl_p/get_next_line_p.h"
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

//pipes_bonus.c
void	ft_redirect_fd(int *prev_pipe, char **commands, int *fd, int i);
void	ft_pipeline(int infile, int outfile, char **commands, char **envp);
int		ft_openfile(char *name_file, int open_mode);
void	ft_heredoc(int infile, int outfile, char *limit, char **argv);

//inputs_bonus.c
int		check_command(char *command, char **envp);

//utils_bonus.c
void	ft_print_help(void);
void	ft_dup_close(int fd1, int fd2, int fd_close);
void	ft_close_all(int *fd1, int *fd2);
int		ft_count_string(char **string);

#endif