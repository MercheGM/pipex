/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/19 21:50:10 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Function counts number of strings*/
int	ft_count_string(char **string)
{
	int	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
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
	int i = 0;
	args = ft_split(command, ' ');
	if (args == NULL)
		exit (errno);
	else if (ft_count_string(args) == 1)
		args = ft_add_null(args);
	envp = ft_add_null(envp);
	path = ft_strjoin("/bin/", args[0]);
	if (access(path, X_OK) < 0)
	{
		path = ft_memfree(path);
		perror("access");
		exit (errno);
	}
	//printf("conteo: %s\n",path);
	/*while (i < ft_count_string(args))
	{
		printf("%d: %s\n", i , args[i]);
		i++;
	}*/
	if (execve(path, args, envp) == -1)
	{
		perror("execve");
		exit(errno);
	}
	return (errno);
}
