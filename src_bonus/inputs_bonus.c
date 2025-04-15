/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/15 22:07:05 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Function counts number of commands*/
static int	ft_len_command(char **commands)
{
	int	len;

	len = 0;
	while (commands[len])
		len++;
	return (len);
}

/*Function adds NULL to the end of the args pointer*/
static char	**ft_add_null(char **args)
{
	char	**aux;

	aux = (char **)ft_calloc(2, sizeof(char *));
	aux[0] = (char *)ft_calloc(ft_strlen(args[0]) + 1, sizeof(char *));
	ft_memcpy(aux[0], args[0], ft_strlen(args[0]));
	aux[1] = NULL;
	args[0] = ft_memfree(args[0]);
	args = NULL;
	return (aux);
}

/*Checks the command and excecutes it. Funtion checks first if the command
exits and then it splits the info from the command and gets the enviroment
info where it's going to be excecuted the command*/
int	check_command(char *command, char **envp)
{
	char	*path;
	char	**args;

	args = ft_split(command, ' ');
	if (args == NULL)
		exit (errno);
	else if (ft_len_command(args) == 1)
		args = ft_add_null(args);
	path = ft_strjoin("/bin/", args[0]);
	if (access(path, X_OK) < 0)
	{
		path = ft_memfree(path);
		perror("access");
		exit (errno);
	}
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(errno);
	}
	return (errno);
}
