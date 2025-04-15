/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/15 21:46:05 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		*fd[2];
	//int		fd2[2];
	pid_t	pid;
	int		status;
	int		cont;
	
	cont = 2;
	if (argc >= 5)
	{
		while (cont < argc - 2)
		{
			if (pipe(*fd) != 0)
				return (1);
			pid = fork();
			if (pid == 0)
			{
				if (cont == 2)
				{
					printf("\tHIJO PID: %d. Accede al comando: %s. Contador: %d\n", getpid(), argv[cont], cont);
					ft_first_child(*fd, argv[cont], argv[cont - 1], envp);
					exit (0);
					//abrimos fichero input
				}
				/*else if (cont == argc - 1)
				{
					printf("\tHIJO PID: %d. Accede al comandooo00o0o: %s\n", getpid(), argv[cont]);
					exit (0);
				}*/
					//abrimos fichero output
				else if (cont < argc - 2)
				{
					printf("\tHIJO PID: %d. Accede al comando: %s. Contador: %d. Contador - 2: %d\n", getpid(), argv[cont], cont, cont -2);
					ft_middle_child(*fd, argv[cont], envp);
					perror("after child_n");
					exit (0);
				}
					//status = ft_child(fd, argv[2], argv[1], envp);
			}
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
			ft_parent(*fd, argv[cont], argv[cont + 1], envp);
		}
	}
	else
		ft_print_help();
	return (0);
}
