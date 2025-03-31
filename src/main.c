/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/31 21:14:35 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_child(int *fd, char *argv[])
{
	char *path = "/bin/cat";
	char *args[] = {"/bin/cat", NULL};
    char *envp[] = {"PATH=/bin/", NULL};
	
	int fd_file = open("src/main.c", O_RDONLY);
	if (fd_file > 0)
	{
		close(fd[READ]); /*cerramos extremo no necesario*/
		printf("primer hijo: %d\n", getpid());
		dup2(fd_file, STDIN_FILENO);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		if (execve(path,args, envp) == -1)
		{
			printf("cierro fd_file\n");
			close(fd_file);
			exit(1);
		}
		exit (0);
	}
	else
		ft_printf("error abriendo fichero de entrada\n");
		
}

int	ft_parent(int *fd, char *command, char *outfile)
{
	int fd_file;
	char *path = "/bin/wc";
	char *args[] = {"/bin/wc", "-l",NULL};
	char *envp[] = {"PATH=/bin/", NULL};
	
	printf("padre: %d\n", getpid());
	close(fd[WRITE]); 
	printf("outfile: %s\n", outfile);
	fd_file = open(outfile, O_CREAT |  O_WRONLY, 0644);  /*utilizar O_EXCL para NO sobreescribir el fichero*/
	if (fd_file > 0)
	{
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
		if (execve(path,args, envp) == -1)
		{
			printf("cierro fd_file\n");
			close(fd_file);
			exit(1);
		}
	}
	close(fd[READ]);
}

int main(int argc, char *argv[])
{
	int fd[2];
	char **info;
	pid_t pid;
	int status;
	char buf[50];
	int num_bytes;
	
	if (argc == 5)
	{
		info = ft_split(*argv, " "); //ver qué se recibe y separar los argumentos
		printf("0: %s\n", info[0]);
		printf("1: %s\n", info[1]);
		printf("2: %s\n", info[2]);
		printf("3: %s\n", info[3]);
		printf("4: %s\n", info[4]);
		if (pipe(fd) != 0)
			return (1);
		pid = fork();
		if (pid == 0)  //primer hijo
		{
			ft_child(fd, argv);
		}
		else //estamos en el padre
		{
			waitpid(pid, &status, 0);
			ft_parent(fd, info[3], info[4]);
		}
	}
	else 
		ft_printf("ERROR: Invalid inputs. Please introduce:\n./pipex infile command1 command2 outfile\n");
	return (0);
}
