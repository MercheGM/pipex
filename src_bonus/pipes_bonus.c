/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:21:46 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/26 13:48:47 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirect_fd(int *prev_pipe, char **commands, int *fd, int i)
{
	int	num_commands;
	int	fd_outfile;

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

void	ft_pipeline(int infile, int outfile, char **commands, char **envp)
{
	int	i;
	int	fd[2];
	int	status;
	int	pid;
	int	prev_pipe[2];

	prev_pipe[0] = infile;
	prev_pipe[1] = outfile;
	i = 1;
	while (++i <= ft_count_string(commands) - 2)
	{
		if (i < ft_count_string(commands) - 2)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			ft_redirect_fd(prev_pipe, commands, fd, i);
			check_command(commands[i], envp);
		}
		else
		{
			close(fd[WRITE]);
			prev_pipe[0] = fd[READ];
			waitpid(pid, &status, 0);
		}
	}
	ft_close_all(fd, prev_pipe);
	exit(EXIT_SUCCESS);
}

int	ft_openfile(char *name_file, int open_mode)
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

void	ft_heredoc(int infile, int outfile, char *limit, char **argv)
{
	char *line;
	bool end;
	
	end = false;
	
	while (!end)
	{
		line = ft_gnl(STDIN_FILENO);
		if (ft_strncmp(line, limit, ft_strlen(limit) + 1))
			break;
		else
			write(infile, line, ft_strlen(line));
	}
}