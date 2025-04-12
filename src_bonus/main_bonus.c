/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/12 11:57:42 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (argc == 5)
	{
		if (pipe(fd) != 0)
			return (1);
		pid = fork();
		if (pid == 0)
			status = ft_child(fd, argv[2], argv[1], envp);
		else
		{
			waitpid(pid, &status, 0);
			if (WEXITSTATUS(status) == 0)
				ft_parent(fd, argv[3], argv[4], envp);
			else
				exit(WEXITSTATUS(status));
		}
	}
	else
		ft_print_help();
	return (0);
}
