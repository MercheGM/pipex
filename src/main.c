/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/09 20:48:43 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_dup_close(int *fd_old, int fd_new)
{
	dup2(*fd_old, fd_new);
	close(*fd_old);
	return (errno);
}

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
		perror("child");
		exit(errno);
	}
	return (errno);
}

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
	perror("parent");
	exit(errno);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;
	int		status;
	char	*aux;
	
	if (argc == 5)
	{
		if (pipe(fd) != 0)
			return (1);
		pid = fork();
		if (pid == 0)
			status = ft_child(fd, argv[2], argv[1], envp);
		else
		{
			waitpid(pid, &status, 0);
			if (WEXITSTATUS(status) == 0)
				ft_parent(fd, argv[3], argv[4], envp);
			else
				exit(WEXITSTATUS(status));
		}
	}
	else
		ft_printf("ERROR: Invalid inputs. Please introduce:\n./pipex infile command1 command2 outfile\n");
	return (0);
}
