/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/25 17:25:33 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
    /*int err; 
    int fd = access("/bin/", F_OK);
    if (fd == -1) {
        printf("Error Number: %d\n", errno);
        perror("Error Description:");
    } else {
        printf("No error\n");
    }*/
    const char *path = "/bin/wc";
    char *const command[] = { "/bin/wc", "-a", NULL };
    char *const envp[] = { "PATH=/bin", NULL };

    //execve(path, command, envp);
    check_argv(argc, argv);

    // Si execve tiene éxito, este código no se alcanza
    perror("execve");  // Solo se ejecuta en caso de error
    return (0);
}