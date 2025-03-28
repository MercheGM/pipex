/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/28 20:22:15 by mergarci         ###   ########.fr       */
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

char *check_command(char *command)
{
    char *path;
    
    path = ft_strjoin("/bin/", command);
    //printf("%s\n", path);
    if (access(path, X_OK) < 0)
    {
        free(path);
        path = NULL;
    }
    return (path);
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
				out[i] = check_file(argv[i + 1], i);
			}
            else if (i == argc - 2) //ultimo fichero
            {
				out[i] = check_file(argv[i + 1], i);
			}
            else
            {
		        out[i] = check_command(argv[i + 1]);		
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
