/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/24 21:24:18 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_hijo(int *prev_pipe, char **commands, int *fd, int i)
{
	int num_commands;
	int fd_outfile;
	char buf[10];

	num_commands = ft_count_string(commands);
	
	//printf("\n\nNum commands: %d, i: %d, %s prev_pipe[0] = %d\n", num_commands, i, commands[i], prev_pipe[0]);
	if (prev_pipe[0] != -1) {

	//	printf("Si existe un pipe previo, prev_pipe[0]: %d\n ", prev_pipe[0]);
		// Si existe un pipe previo, redirigir su salida a la entrada estándar
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(fd[READ_END]);
	}
	else
	{
	//	printf("NOOOOOOOOOOOOO existe un pipe previo, prev_pipe[0]: %d\n", prev_pipe[0]);
		close(prev_pipe[0]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
	}

	if (i < num_commands - 2) 
	{

	//	printf("No es el ultimo comando\n ");
		// Si no es el último comando, redirigir la salida a un pipe
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		close(prev_pipe[1]);
	}
	else
	{
		//printf("ultimo comando\n ");
		//read(fd[READ], buf, 10);
		//write(prev_pipe[1], buf, 10);
		//printf("Último comando. fd_outfile: %d\n", prev_pipe[1]);
		dup2(prev_pipe[1], STDOUT_FILENO);
		close(prev_pipe[1]);
		close(fd[WRITE_END]);
	}

	// Cerrar los extremos del pipe que no estamos utilizando
	//close(fd[READ_END]);
	//close(fd[WRITE_END]);

}

void execute_pipeline(int fd_infile, int fd_outfile, char **commands, char **envp)
{
    int i;
	int fd[2];
    int status;
	int pid;
    int prev_pipe[2];
	int argc;

	argc = ft_count_string(commands);	
	prev_pipe[0] = fd_infile;
	prev_pipe[1] = fd_outfile;
	i = 2;
    while (i <= argc - 2)
	{
        if (i  < argc -2)
			pipe(fd);  // Crear un pipe para cada par de procesos
		//printf("fd[R]: %d, fd[W]: %d\n", fd[READ], fd[WRITE]);
        pid = fork();
        if (pid == 0) 
		{  // Proceso hijo
		//	printf("comando: %d: %s", i, commands[i]);
            ft_hijo(prev_pipe, commands, fd, i);
			check_command(commands[i],envp);
			exit(1);  // En caso de que execvp falle
        } 
		else 
		{  // Proceso padre
            close(fd[WRITE_END]);
            prev_pipe[0] = fd[READ_END];	
			waitpid(pid, &status, 0);			
		}
		i++;
    }
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	close(prev_pipe[0]);
	close(prev_pipe[1]);

}

int main(int argc, char *argv[], char *envp[])
{
	int fd_infile;
	int fd_outfile;

	if (argc < 5)
	{
		ft_print_help();
		exit (EXIT_FAILURE);
	}
	if (argc == 6 && !ft_strncmp(argv[1], "here_doc", 8))
	{
		printf("here!\n");
		fd_outfile = open(argv[argc-1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_outfile == -1)
		{
			perror("outfile");
			exit(errno);
		}
	}
	else
	{
		fd_infile = open(argv[1], O_RDONLY);
		if (fd_infile == -1)
		{
			perror("infile");
			exit(errno);
		}
		fd_outfile = open(argv[argc-1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_outfile == -1)
		{
			perror("outfile");
			exit(errno);
		}
	    execute_pipeline(fd_infile, fd_outfile, argv, envp);
	}
    return 0;
}

	

	
	
