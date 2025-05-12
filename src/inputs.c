/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/12 20:36:09 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Free a ptr strings*/
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

/*Free 3 strings as inputs*/
static void	ft_free_strings(char **str1, char ***str2, char ***str3)
{
	*str1 = ft_memfree(*str1);
	*str2 = ft_free_str(*str2);
	*str3 = ft_free_str(*str3);
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
int	check_exec(char *command, char **envp, int status)
{
	char	*path;
	char	**args;

	args = ft_split_bash(command);
	if (!status || (args == NULL))
	{
		envp = ft_add_null(envp);
		path = ft_strjoin("/usr/bin/", args[0]);
		if (access(path, X_OK) == -1)
		{
			ft_free_strings(&path, &args, &envp);
			perror("access");
			return (EXIT_FAILURE);
		}
		if (execve(path, args, envp) == -1)
		{
			ft_free_strings(&path, &args, &envp);
			perror("execve");
			return (EXIT_FAILURE);
		}
		ft_free_strings(&path, &args, &envp);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*Only to be used at parent process. It closes fd[WRITE], copies
 fd[READ] to the previous fd*/
void	ft_parent(int *fd, int *fd_saved)
{
	ft_closefd_save(fd[WRITE]);
	fd_saved[READ] = fd[READ];
}
