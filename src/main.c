/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/30 23:58:42 by mergarci         ###   ########.fr       */
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
		printf("primer hijo: %d\n", getpid());
		dup2(fd_file, STDIN_FILENO);
		//close(fd[READ]); /*cerramos extremo no necesario*/
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		execve(path,args, envp);
		//execlp("/bin/cat", "cat", NULL);
		close(fd_file);
		exit (0);
	}
	else
		ft_printf("error abriendo fichero de entrada\n");
}
int main(int argc, char *argv[])
{
	int fd[2];
	int fd_file;
	pid_t pid;
	int status;
	char buf[50];
	int num_bytes;

	char *path = "/bin/wc";
	char *args[] = {"/bin/wc", "-l",NULL};
    char *envp[] = {"PATH=/bin/", NULL};
	
	if (argc == 5)
	{
		if (pipe(fd) != 0)
			return (1);
		pid = fork();
		if (pid == 0)  //primer hijo. El que ejecuta ls
		{
			ft_child(fd, argv);
		}
		else //estamos en el padre
		{
			waitpid(pid, &status, 0);
			printf("padre: %d\n", getpid());
			close(fd[WRITE]); /*cerramos extremo no necesario*/
			/*num_bytes = read(fd[READ], buf, sizeof(buf));
			printf("%d: %s\n", num_bytes, buf);*/
			fd_file = open(FILE_NAME, O_WRONLY);
			printf("fd2: %d\n", fd_file);
			if (fd_file > 0)
			{
				dup2(fd[READ], STDIN_FILENO);
				close(fd[READ]);
				dup2(fd_file, STDOUT_FILENO);
				close(fd_file);
				execve(path,args, envp);
			}
			close(fd[READ]);
		}
	}
	else 
		ft_printf("ERROR: Invalid inputs. Please introduce:\n./pipex infile command1 command2 outfile\n");
	return (0);
}