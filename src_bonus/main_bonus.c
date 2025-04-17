/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/17 15:33:07 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*int	main(int argc, char *argv[], char *envp[])
{
	//int		*fd[2];
	int		fd[2];
	int		fd2[2];
	pid_t	pid;
	int		status;
	int		cont;
	
	cont = 2;
	if (argc >= 5)
	{
		while (cont < argc - 2)
		{
			fd2[READ] = fd[READ];
			fd2[WRITE] = fd[WRITE];
			printf("W%d-fd[WRITE]: %d, fd[READ]: %d\n", cont, fd[WRITE], fd[READ]);
			printf("W%d-fd2[WRITE]: %d, fd2[READ]: %d\n", cont, fd2[WRITE], fd2[READ]);
			if (pipe(fd) != 0)
				return (1);
			pid = fork();
			if (pid == 0)
			{
				if (cont == 2)
				{
					//fd2[READ] = fd[READ];
					//fd2[WRITE] = fd[WRITE];
					printf("fd[WRITE]: %d, fd[READ]: %d\n", fd[WRITE], fd[READ]);
					printf("fd2[WRITE]: %d, fd2[READ]: %d\n", fd2[WRITE], fd2[READ]);
					printf("\tHIJO PID: %d. Accede al comando: %s. Contador: %d\n", getpid(), argv[cont], cont);
					ft_first_child(fd, fd2, argv[cont], argv[cont - 1], envp);
					exit (0);
					//abrimos fichero input
				}

					//abrimos fichero output
				else if (cont <= argc - 2)
				{
					printf("fd[WRITE]: %d, fd[READ]: %d\n", fd[WRITE], fd[READ]);
					printf("fd2[WRITE]: %d, fd2[READ]: %d\n", fd2[WRITE], fd2[READ]);

					printf("\tHIJO PID: %d. Accede al comando: %s. Contador: %d. Contador - 2: %d\n", getpid(), argv[cont], cont, cont -2);
					ft_middle_child(fd, fd2, argv[cont], envp);
					perror("after child_n");
					exit (0);
				}
					//status = ft_child(fd, argv[2], argv[1], envp);
			}
			//printf("descritpr lectura: %d\n", fd[WRITE]);
			waitpid(pid, &status, 0);
			//else
			//{
			//	waitpid(pid, &status, 0);
				//ft_parent(fd, argv[cont], argv[cont + 1], envp);
			//}
			
			//waitpid(pid, &status, 0);
			//perror("after wait");
			cont++;
		}
		
		if (cont == argc - 1)
		{
			printf("PADRE PID: %d.Accede al comando: %s. Contador: %d\n", getpid(),argv[cont], cont);
			ft_parent(fd, argv[cont], argv[cont + 1], envp);
		}
	}
	else
		ft_print_help();
	return (0);
}*/


int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		fd2[2];
	pid_t	pid;
	int		status;
	int		cont;
	int prev_pipe_fd;   // Descripción para el pipe del comando anterior
	int		fd_outfile;
	int		fd_infile;
	
	if (argc >= 5)
	{
		cont = 2;
		prev_pipe_fd = -1;
		while (cont <= argc - 2)
		{
			if (cont != argc -2)
			{
				if (pipe(fd) != 0)
					exit (errno);
			}
			pid = fork();
			if (pid < 0) {
				perror("fork");
				exit(errno);
			}
			if (pid == 0)
			{
				ft_child_2(prev_pipe_fd, fd, cont, argv, envp);
				exit(0);
			}
			waitpid(pid, &status, 0);
			if (prev_pipe_fd != -1)
            	close(prev_pipe_fd);

	        // Para el siguiente proceso, el extremo de lectura del pipe actual será la entrada
	        if (cont < argc - 2) {
	            close(fd[WRITE]);  // Cerramos el extremo de escritura en el padre
	            prev_pipe_fd = fd[READ];
	        }
			
			cont++;
		}
	}
	else
		ft_print_help();
	return (0);
}
	
