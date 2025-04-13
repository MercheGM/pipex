/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/13 21:24:53 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Checks the command and excecutes it. Funtion checks first if the command
exits and then it splits the info from the command and gets the enviroment
info where it's going to be excecuted the command*/
int	check_command(char *command, char **envp)
{
	char	*path;
	char	**args;
	//perror(command);
	args = ft_split(command, ' ');
	if (args == NULL)
		exit (errno);
	path = ft_strjoin("/bin/", args[0]);
	if (access(path, X_OK) < 0)
	{
		path = ft_memfree(path);
		perror("access");
		exit (errno);
	}
	perror("hola");
	//execve(path, args, envp_final);
	//perror("after execve");
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(errno);
	}
	perror("holaaa");

	return (errno);
}
