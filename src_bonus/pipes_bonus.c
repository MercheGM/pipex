/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:21:46 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/04 14:53:29 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Function to duplicate file descriptors depending on the number
of the proccess. This function duplicates and closes fd*/
void	ft_redirect_fd(int *prev_pipe, char **commands, int *fd, int i)
{
	int	num_commands;

	num_commands = ft_count_string(commands);
	if (prev_pipe[0] != -1)
		ft_dup_close(prev_pipe[0], STDIN_FILENO, fd[READ]);
	else
		ft_dup_close(fd[READ], STDIN_FILENO, prev_pipe[READ]);
	if (i < num_commands - 2)
		ft_dup_close(fd[WRITE], STDOUT_FILENO, prev_pipe[WRITE]);
	else
		ft_dup_close(prev_pipe[1], STDOUT_FILENO, fd[WRITE]);
}

/*It manange the pipelines and execute the commands */
void	ft_pipeline(int *files, char **commands, char **envp)
{
	int	i;
	int	fd[2];
	int	status;
	int	pid;
	int	prev_pipe[2];

	prev_pipe[READ] = files[I];
	prev_pipe[WRITE] = files[O];
	i = 1;
	status = 0;
	while (++i <= ft_count_string(commands) - 2)
	{
		if (i < ft_count_string(commands) - 2)
			ft_create_fd(fd);
		pid = fork();
		if (pid == 0)
		{
			ft_redirect_fd(prev_pipe, commands, fd, i);
			check_command(commands[i], envp);
		}
		else
			ft_parent(fd, prev_pipe, pid, &status);
	}
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

/*Function that reads the STDIN input. It will check if the
new line is the limit or not in order to exit the loop*/
void	ft_read_heredoc(int fd, char *limit)
{
	char	*line;
	char	*newlimit;

	newlimit = ft_strjoin(limit, "\n");
	while (1)
	{
		ft_printf("> ");
		line = ft_gnl(STDIN_FILENO);
		if (ft_strncmp(line, newlimit, ft_strlen(newlimit) + 1) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_memfree(line);
	}
	ft_memfree(newlimit);
	ft_memfree(line);
}

/*It creates a new process to read SDTIN input and saves it 
in the file descriptor input*/
void	ft_heredoc(int *files, char *limit)
{
	int	fd[2];
	int	pid;
	int	status;

	status = 0;
	ft_create_fd(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[READ]);
		ft_read_heredoc(fd[WRITE], limit);
		close(fd[WRITE]);
		exit(errno);
	}
	else
		ft_parent(fd, files, pid, &status);
}
