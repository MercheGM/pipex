/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/03/28 20:24:10 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
    char **inputs;
    const char *path = "/bin/wc";
    char *const command[] = { "/bin/wc", "-a", NULL };
    char *const envp[] = { "PATH=/bin", NULL };

    //execve(path, command, envp);
    inputs = check_argv(argc, argv);
	if (inputs)
		printf("todo ok!\n");
	else
		printf("caca\n");
    // Si execve tiene éxito, este código no se alcanza
    perror("execve");  // Solo se ejecuta en caso de error
    return (0);
}