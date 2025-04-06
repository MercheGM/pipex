/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/06 21:23:30 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *check_file(char *file, int i)
{
    char *path;
    int fd;
	

	fd = 0;
    path = ft_strjoin("./", file);
    //printf("hola! %d\n", i);
	if (i == 0)
	{
	    if (access(path, R_OK) < 0)
	    {
			path = free_memory(path);
	    }
	}
	else
	{
		if (access(path, F_OK) != 0)
		{
			fd = open(path, O_CREAT | O_CREAT, 0644);
			printf("fd: %d\n", fd);
			if (fd != -1)
				close(fd);
		}
	}
    return (path);
}

int check_command(char *command)
{
    char *path;
	char **args;
    char *envp[] = {"PATH=/bin/", NULL};
	char **aux;
	int len;

	len = 0;
	aux = ft_split(command, ' ');
	if (aux == NULL)
		exit (errno);
	while (aux[len])
		len++;
    path = ft_strjoin("/bin/", aux[0]);
    if (access(path, X_OK) < 0)
    {
        free(path);
        path = NULL;
		perror("access");
		exit (errno);
    }
	args = ft_calloc(len + 1, sizeof(char *));
	if (args == NULL)
		exit (errno);
	args[0] = path;
	if (len == 2)
		args[1] = aux[1];
	args[len] = NULL;
	if (execve(path,args, envp) == -1)
		{
			//close(fd_file);
			perror("child");
			exit(errno);
		}
    return (0);
}

char **check_argv(int argc, char *argv[])
{
    int i;
    char **out;

    if (argc >= 5)
    {
        out = ft_calloc(argc - 1, sizeof(char *));
        while (i < argc - 1)
        {
            if (i == 0) // primer fichero
            {
				//out[i] = check_file(argv[i + 1], i);
			}
            else if (i == argc - 2) //ultimo fichero
            {
				//out[i] = check_file(argv[i + 1], i);
			}
            else
            {
		       // out[i] = check_command(argv[i + 1]);		
            }
			if (out[i] == NULL)
				{
					while (i)
					{
						out[i] = free_memory(out[i]);
						i--;
					}
					free(out);
					out = NULL;
					break;
				}
			printf("%d: %s\n", i, out[i]);
			i++;
        }
    }
    return (out);
}
