/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/12 11:57:37 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Function to fill info with the enviroment info and the PATH variable*/
static char	**ft_fill_envp(char **envp)
{
	char	**aux;

	aux = ft_calloc(3, sizeof(char *));
	aux[0] = "PATH=/usr/bin:/bin";
	aux[1] = envp[0];
	aux[2] = NULL;
	return (aux);
}

/*Checks the command and excecutes it. Funtion checks first if the command
exits and then it splits the info from the command and gets the enviroment
info where it's going to be excecuted the command*/
int	check_command(char *command, char **envp)
{
	char	*path;
	char	**args;
	char	**envp_final;

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
	envp_final = ft_fill_envp(envp);
	if (execve(path, args, envp_final) == -1)
	{
		perror("execve");
		exit(errno);
	}
	return (errno);
}
