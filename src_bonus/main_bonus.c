/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/16 19:27:40 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_exec_pipex(int *file, char **argv, char **envp, int *status)
{
	int	argc;

	argc = ft_count_string(argv);
	if (argc == 6 && (!ft_strncmp(argv[1], "here_doc", 9)))
	{
		file[I] = -1;
		file[O] = ft_openfil(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND);
		ft_heredoc(file, argv[2]);
		argv++;
	}
	else if (argc == 6 && !ft_strncmp(argv[1], "here_doc", 1))
		ft_print_help();
	else
	{
		file[I] = ft_openfil(argv[1], O_RDONLY);
		file[O] = ft_openfil(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
	}
	*status = ft_pipeline(file, argv, envp);
	if (file[O] == -1)
		*status = 1;
}

int	main(int argc, char *argv[], char *envp[])
{
	int	file[2];
	int	status;

	status = 1;
	if (argc >= 5)
	{
		ft_exec_pipex(file, argv, envp, &status);
		ft_closefd(file[I]);
		ft_closefd(file[O]);
	}
	else
		ft_print_help();
	return (status);
}
