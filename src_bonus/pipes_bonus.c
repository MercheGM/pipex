/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:21:46 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/19 18:08:19 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Function to manage fd's child process. It check the command and execute it*/
int	ft_first_child(int *fd, int *fd_next, char *command, char *infile, char **envp)
{
	int	fd_file;
	
	fd_file = open(infile, O_RDONLY);
	//printf("fd: %d\n", fd_file);
	if (fd_file > 0)
	{
		//close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		//close(fd[WRITE]);
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

/*Function to manage fd's child process. It check the command and execute it*/
int	ft_middle_child(int *fd_new, int *fd_old, char *command, char **envp)
{
	int	fd_file;
	int fd_prev[2];
	//fd_file = open(infile, O_RDONLY);
	if (fd_old[READ] == -1)
	{
		perror("errno");
	}
	//{
	//	close(fd[READ]);
	
	
	//dup2(fd_old[READ], STDIN_FILENO);
	//close(fd_old[WRITE]);
	dup2(fd_new[WRITE], STDOUT_FILENO);
	dup2(fd_new[READ], STDIN_FILENO);

	//close(fd_new[READ]);
	check_command(command, envp);
	perror("eoo");
	exit (0);
	/*}
	else
	{
		perror(infile);
		exit(errno);
	}*/
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

int		ft_child_2(int *prev_pipe_fd, int *fd, int cont, char **argv, char **envp)
{
	int fd_file;
	//int fd_outfile;
	int argc;
	int aux = 0;
	
	fd_file = -1;
	argc = ft_count_string(argv);
	printf("\tHIJO PID: %d. Accede al comando: %s. Contador: %d. Contador - 2: %d\n", getpid(), argv[cont], cont, cont -2);

	/*if (*prev_pipe_fd != -1)
	{
		if (dup2(*prev_pipe_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 (prev_pipe_fd)");
			exit(errno);
		}
		close(prev_pipe_fd);
	}*/
	if (cont == 2) //primer hijo
	{
		fd_file = open(argv[cont - 1], O_RDONLY);
		if (fd_file < 0)
		{
			perror(argv[cont + 1]);
			exit(errno);
		}
		dup2(fd[WRITE], STDOUT_FILENO);
		dup2(fd_file, STDIN_FILENO);

	}
	else if (cont < argc - 2) //hijos intermedios
	{
		dup2(fd[READ], STDIN_FILENO);
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
		{
			perror(ft_itoa(cont));
			exit(EXIT_FAILURE);
		}

	}
	else if (cont == argc - 2) //ultimo hijo
	{
		printf(".%s.\n",argv[cont + 1]);
		fd_file = open(argv[cont + 1], O_CREAT | O_WRONLY, 0644);
		
		if (fd_file < 0)
		{
			perror(argv[cont + 1]);
			exit(errno);
		}
		dup2(fd[READ], STDIN_FILENO);
		if (dup2(fd_file, STDOUT_FILENO) == -1)
		{
			perror("dup2 (fd[WRITE])");
			exit(EXIT_FAILURE);
		}
	}
	//cleardup2(*prev_pipe_fd, fd[READ]);
//	*prev_pipe_fd = fd[READ];
	aux = fd[READ];
	close(fd[READ]);
	close(fd[WRITE]);

	//if (prev_pipe_fd != -1)
//		close(prev_pipe_fd);
	/*if (cont < argc - 2)
	{
		close(fd[READ]); // extremo de lectura
		close(fd[WRITE]); // extremo de escritura (ya duplicado)
	}*/

	//cont++;
	return (aux);
}
