/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:42:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/10 17:50:08 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_fill_info(char **aux, char *path, int len)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_calloc(len + 1, sizeof(char *));
	if (args == NULL)
		exit (errno);
	while (i < len)
	{
		args[i] = aux[i];
		i++;
	}
	args[len] = NULL;
	return (args);
}

char	**ft_fill_envp(char **envp)
{
	char	**aux;

	aux = ft_calloc(3, sizeof(char *));
	aux[0] = "PATH=/usr/bin:/bin";
	aux[1] = envp[0];
	aux[2] = NULL;
	return (aux);
}

int	ft_len_command(char **commands)
{
	int	len;

	len = 0;
	while (commands[len])
		len++;
	return (len);
}

int	check_command(char *command, char **envp)
{
	char	*path;
	char	**args;
	char	**envp_final;
	char	**aux;

	aux = ft_split(command, ' ');
	if (aux == NULL)
		exit (errno);
	path = ft_strjoin("/bin/", aux[0]);
	if (access(path, X_OK) < 0)
	{
		path = ft_memfree(path);
		perror("access");
		exit (errno);
	}
	args = ft_fill_info(aux, path, ft_len_command(aux));
	envp_final = ft_fill_envp(envp);
	if (execve(path, args, envp) == -1)
	{
		perror("child");
		exit(errno);
	}
	return (errno);
}
