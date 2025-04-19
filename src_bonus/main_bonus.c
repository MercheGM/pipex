/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/19 21:51:35 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_hijo(int *prev_pipe, int num_commands, int *fd, int i)
{
	int fd_outfile;
	
	if (prev_pipe[0] != -1) {
		// Si existe un pipe previo, redirigir su salida a la entrada estándar
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
	}

	if (i < num_commands - 1) 
	{
		// Si no es el último comando, redirigir la salida a un pipe
		dup2(fd[WRITE_END], STDOUT_FILENO);
	}
	else
	{
		dup2(prev_pipe[1], STDOUT_FILENO);
	}

	// Cerrar los extremos del pipe que no estamos utilizando
	close(fd[READ_END]);
	close(fd[WRITE_END]);

}

void execute_pipeline(int fd_infile, char **commands, char **envp)
{
    int i;
	int fd[2];
    int status;
	int pid;
    int prev_pipe[2];
	int argc;

	argc = ft_count_string(commands);	
	prev_pipe[0] = fd_infile;
	prev_pipe[1] = -1;
	i = 2;
    while (i <= argc - 2)
	{
        pipe(fd);  // Crear un pipe para cada par de procesos
        pid = fork();
        if (pid == 0) 
		{  // Proceso hijo
			if (i == argc - 2)
			{
				prev_pipe[1] = open(commands[i+1], O_CREAT | O_WRONLY, 0644);
				if (prev_pipe[1] == 1)
				{
					perror("outfile");
					exit(errno);
				}
			}
			printf("comando a ejecutar: %s\n", commands[i]);
            ft_hijo(prev_pipe, argc - 2, fd, i);
			// Ejecutar el comando correspondiente
			check_command(commands[i],envp);
			//execve(commands[i][0], commands[i], envp);
			perror("execvp failed");
			exit(1);  // En caso de que execvp falle
        } 
		else 
		{  // Proceso padre
			waitpid(pid, &status, 0);
            close(fd[WRITE_END]);
            if (prev_pipe[0] != -1)
                close(prev_pipe[0]);
			if (fd_infile != -1)
                close(fd_infile);
			if (prev_pipe[1] != -1)
                close(prev_pipe[1]);		
            prev_pipe[0] = fd[READ_END];
        }
		i++;
    }
}

int main(int argc, char *argv[], char *envp[])
{
	int fd_infile;

	if (argc < 5)
	{
		ft_print_help();
		exit (EXIT_FAILURE);
	}
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		perror("infile");
		exit(errno);
	}
    // Ejecutar la tubería de comandos
    execute_pipeline(fd_infile, argv, envp);

    return 0;
}

	

	
	
