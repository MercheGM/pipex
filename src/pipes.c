/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:21:46 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/06 20:47:04 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Function to duplicate file descriptors depending on the number
of the proccess. This function duplicates and closes fd*/
void	ft_redirect_fd(int *prev_pipe, char **commands, int *fd, int i)
{
	int	num_commands;

	num_commands = ft_count_string(commands);
	if (prev_pipe[READ] != -1)
		ft_dup_close(prev_pipe[READ], STDIN_FILENO, fd[READ]);
	else
		ft_dup_close(fd[READ], STDIN_FILENO, prev_pipe[READ]);
	if (i < num_commands - 2)
		ft_dup_close(fd[WRITE], STDOUT_FILENO, prev_pipe[WRITE]);
	else
		ft_dup_close(prev_pipe[WRITE], STDOUT_FILENO, fd[WRITE]);
}

/*It manange the pipelines and execute the commands */
void	ft_pipeline(int *files, char **commands, char **envp)
{
	int	i;
	int	fd[2];
	int	pid;
	int	prev_pipe[2];

	prev_pipe[READ] = files[I];
	prev_pipe[WRITE] = files[O];
	i = 1;
	while ((++i <= ft_count_string(commands) - 2))
	{
		ft_create_fd(fd);
		pid = fork();
		if (pid == 0)
		{
			ft_redirect_fd(prev_pipe, commands, fd, i);
			if (check_command(commands[i], envp) != 0)
				break ;
		}
		else
			ft_parent(fd, prev_pipe);
	}
	while (i-- >= 0)
		wait(NULL);
	ft_close_all(fd, prev_pipe);
}

/*Functions to open files depending of the mode. Besides,
it checks if the file has been opened properly*/
int	ft_openf(char *name_file, int open_mode)
{
	int	fd;

	if (open_mode == O_RDONLY)
		fd = open(name_file, open_mode);
	else
		fd = open(name_file, open_mode, 0644);
	if (fd == -1)
	{
		perror("outfile");
		exit(errno);
	}
	return (fd);
}
