/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:32 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/16 19:06:55 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		exit(1);
	}
}

/*Function that reads the STDIN input. It will check if the
new line is the limit or not in order to exit the loop*/
void	ft_read_heredoc(int fd, char *limit)
{
	char	*line;
	char	*newlimit;

	newlimit = ft_strjoin(limit, "\n");
	while (1)
	{
		ft_printf("> ");
		line = ft_gnl(STDIN_FILENO, newlimit);
		if (!line)
			break ;
		if (ft_strncmp(line, newlimit, ft_strlen(newlimit) + 1) == 0)
		{
			line = ft_memfree(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		line = ft_memfree(line);
	}
	ft_gnl(-10, NULL);
	newlimit = ft_memfree(newlimit);
}

/*It creates a new process to read SDTIN input and saves it 
in the file descriptor input*/
void	ft_heredoc(int *files, char *limit)
{
	int	fd[2];
	int	pid;

	ft_create_fd(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ]);
		ft_read_heredoc(fd[WRITE], limit);
		close(fd[WRITE]);
		exit(errno);
	}
	else
		ft_parent_fd(fd, files);
}
