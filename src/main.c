/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/06 21:26:19 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_dup_close(int *fd_old, int fd_new)
{
	dup2(*fd_old, fd_new);
	close(*fd_old);
	return(errno);
}

int	ft_child(int *fd, char *command, char *infile)
{

	int fd_file = open(infile, O_RDONLY);
	if (fd_file > 0)
	{
		//check_command(command);
		close(fd[READ]); /*cerramos extremo no necesario*/
		printf("primer hijo: %d. FD_FILE: %d\n", getpid(), fd_file);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		dup2(fd_file, STDIN_FILENO);
		/*if (!ft_dup_close(&fd[WRITE], STDOUT_FILENO) && !dup2(fd_file, STDIN_FILENO))
		{
			exit(errno);
		}*/
		printf("err hijo: %d\n", errno);

		check_command(command);
		/*if (execve(path,args, envp) == -1)
		{
			close(fd_file);
			perror("child");
			exit(errno);
		}*/
		exit (0);
	}
	else
	{
		perror("child");
		exit(errno);
	}
	return (errno);	
}

int	ft_parent(int *fd, char *command, char *outfile)
{
	int fd_file;

	printf("padre: %d\n", getpid());
	close(fd[WRITE]); 
	fd_file = open(outfile, O_CREAT | O_WRONLY, 0644);  /*utilizar O_EXCL para NO sobreescribir el fichero*/
	if (fd_file > 0)
	{
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		dup2(fd_file, STDOUT_FILENO);
		/*if (!ft_dup_close(&fd[READ], STDIN_FILENO) && !dup2(fd_file, STDOUT_FILENO))
			exit(errno);*/
		check_command(command);
		/*if (execve(path,args, envp) == -1)
		{
			close(fd_file);
			perror("parent");
			exit(errno);
		}*/
	}
	close(fd[READ]);
	perror("parent");
	exit(errno);
}

int main(int argc, char *argv[])
{
	int fd[2];
	char **info;
	pid_t pid;
	int status;
	char buf[50];
	int num_bytes;
	char *aux;

	if (argc == 5)
	{
		if (pipe(fd) != 0)
			return (1);
		pid = fork();
		if (pid == 0)  //primer hijo
		{
			status = ft_child(fd, argv[2], argv[1]);
		}
		else //estamos en el padre
		{
			waitpid(pid, &status, 0);
			if (WEXITSTATUS(status) == 0)
			{
				ft_parent(fd, argv[3], argv[4]);
			}
			else
			{
				exit(WEXITSTATUS(status));
			}
		}
	}
	else 
		ft_printf("ERROR: Invalid inputs. Please introduce:\n./pipex infile command1 command2 outfile\n");
	return (0);
}
