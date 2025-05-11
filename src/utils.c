/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:32 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/11 21:29:07 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Closes all file descriptors*/
void	ft_close_all(int *fd1, int *fd2)
{
	ft_closefd_save(fd1[READ]);
	ft_closefd_save(fd1[WRITE]);
	ft_closefd_save(fd2[READ]);
	ft_closefd_save(fd2[WRITE]);
}

/*It duplicates fd1 to fd2 and closes it. Besides, it closes fd_close*/
void	ft_dup_close(int fd1, int fd2, int fd_close)
{
	dup2(fd1, fd2);
	ft_closefd_save(fd1);
	ft_closefd_save(fd_close);
}

/*Print help if the inputs are invalid*/
void	ft_print_help(void)
{
	ft_printf("ERROR: Invalid inputs. Please introduce:\n");
	ft_printf("\t./pipex_bonus infile com1 com2 ... comn outfile\n");
	ft_printf("If you want to use HERE_DOC:\n");
	ft_printf("\t./pipex_bonus here_doc <LIMIT> command1 command2 outfile\n");
	exit (EXIT_FAILURE);
}

/*Function counts number of strings*/
int	ft_count_string(char **string)
{
	int	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}

/*Function to create pipe and check any error. It exits if error*/
void	ft_create_fd(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (errno);
	}
}
