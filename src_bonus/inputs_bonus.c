/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/06 19:07:49 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Function to free a char **str */
static char	**ft_free_str(char **str)
{
	int	n;

	n = ft_count_string(str);
	while (n >= 0)
	{
		str[n] = ft_memfree(str[n]);
		n--;
	}
	free(str);
	return (NULL);
}

/*Function adds NULL to the end of the args pointer*/
static char	**ft_add_null(char **args)
{
	char	**aux;
	int		num;
	int		i;

	num = ft_count_string(args);
	i = 0;
	aux = (char **)ft_calloc(num + 1, sizeof(char *));
	while (i < num)
	{
		aux[i] = (char *)ft_calloc(ft_strlen(args[i]) + 1, sizeof(char *));
		ft_memcpy(aux[i], args[i], ft_strlen(args[i]));
		i++;
	}
	aux[num] = NULL;
	if (num == 1)
	{
		args[0] = ft_memfree(args[0]);
		args = NULL;
	}
	return (aux);
}

/*Checks the command and excecutes it. Funtion checks first if the command
exits and then it splits the info from the command and gets the enviroment
info where it's going to be excecuted the command*/
int	check_command(char *command, char **envp)
{
	char	*path;
	char	**args;

	args = ft_split_bash(command);
	if (args == NULL)
		exit (errno);
	envp = ft_add_null(envp);
	path = ft_strjoin("/usr/bin/", args[0]);
	if (access(path, X_OK) < 0)
	{
		path = ft_memfree(path);
		args = ft_free_str(args);
		envp = ft_free_str(envp);
		perror("access");
		exit(errno);
	}
	if (execve(path, args, envp) == -1)
	{
		path = ft_memfree(path);
		args = ft_free_str(args);
		envp = ft_free_str(envp);
		perror("execve");
		exit(errno);
	}
	return (errno);
}

/*Only to be used at parent process. It closes fd[WRITE], copies
 fd[READ] to the previous fd*/
void	ft_parent(int *fd, int *fd_saved, int *status)
{
	close(fd[WRITE]);
	fd_saved[0] = fd[READ];
	wait(status);
}
