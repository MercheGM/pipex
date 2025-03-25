/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/25 17:45:39 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *check_command(char *command)
{
    char *path;
    
    path = ft_strjoin("/bin/", command);
    printf("%s\n", path);
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
    char *file_in;
    char *file_out;
    char *command1;
    char *command2;
    
    if (argc >= 5)
    {
        out = ft_calloc(argc - 1, sizeof(char *));
        while (i <= argc)
        {
            if (i == 0) // primer fichero
            {}
            else if (i == argc - 1) //ultimo fichero
            {}
            else
            {
                out[i] = check_command(argv[i + 1]);
            }
            file_in = argv[1];
            file_out = argv[argc - 1];
            i++;
            command1 = check_command(argv[1]);
            command2 = check_command(argv[2]);
        }
    }
    return i;
}
