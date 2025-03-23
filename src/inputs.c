/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/23 21:00:50 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_command(char *command)
{
    
}

int check_argv(int argc, char *argv[])
{
    int i;
    char *file_in;
    char *file_out;
    char *command1;
    char *command2;
    
    if (argc >= 5)
    {
        file_in = argv[1];
        file_out = argv[argc - 1];
        command1 = argv[2];
        command2 = argv[3];
    }
}
