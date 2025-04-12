/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:21:46 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/12 11:20:20 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Function to manage fd's child process. It check the command and execute it*/
int	ft_child(int *fd, char *command, char *infile, char **envp)
{
	int	fd_file;

	fd_file = open(infile, O_RDONLY);
	if (fd_file > 0)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		dup2(fd_file, STDIN_FILENO);
		check_command(command, envp);
		exit (0);
	}
	else
	{
		perror(infile);
		exit(errno);
	}
	return (errno);
}

/*Function to manage fd's parent process. It check the command and execute it*/
int	ft_parent(int *fd, char *command, char *outfile, char **envp)
{
	int	fd_file;

	close(fd[WRITE]);
	fd_file = open(outfile, O_CREAT | O_WRONLY, 0644);
	if (fd_file > 0)
	{
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		dup2(fd_file, STDOUT_FILENO);
		check_command(command, envp);
	}
	close(fd[READ]);
	perror(outfile);
	exit(errno);
}

/*Print help if the inputs are invalid*/
void	ft_print_help(void)
{
	ft_printf("ERROR: Invalid inputs. Please introduce:\n");
	ft_printf("./pipex infile command1 command2 outfile\n");
}
