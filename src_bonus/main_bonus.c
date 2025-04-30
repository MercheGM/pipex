/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/30 19:49:14 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	file[2];

	if (argc >= 5)
	{
		if (argc == 6 && !ft_strncmp(argv[1], "here_doc", 8))
		{
			file[IN] = ft_openfile("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC);
			file[OUT] = ft_openfile(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND);
			ft_heredoc(file, argv[2], argv);
			argv++;
		}
		else
		{
			file[IN] = ft_openfile(argv[1], O_RDONLY);
			file[OUT] = ft_openfile(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
			//ft_pipeline(file[IN], file[OUT], argv, envp);
		}
		ft_pipeline(file, argv, envp);
	}
	else
	{
		ft_print_help();
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
