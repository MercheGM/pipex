/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/03 13:24:17 by mergarci         ###   ########.fr       */
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
			file[I] = -1;
			file[O] = ft_openf(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND);
			ft_heredoc(file, argv[2]);
			argv++;
		}
		else
		{
			file[I] = ft_openf(argv[1], O_RDONLY);
			file[O] = ft_openf(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
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
