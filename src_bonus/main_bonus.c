/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/04 21:04:25 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	file[2];

	if (argc >= 5)
	{
		if (argc == 6 && !ft_strncmp(argv[1], "here_doc", 9))
		{
			file[I] = -1;
			file[O] = ft_openf(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND);
			ft_heredoc(file, argv[2]);
			argv++;
		}
		else if (argc ==6 && !ft_strncmp(argv[1], "here_doc", 1))
			ft_print_help();
		else
		{
			file[I] = ft_openf(argv[1], O_RDONLY);
			file[O] = ft_openf(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
		}
		ft_pipeline(file, argv, envp);
	}
	else
		ft_print_help();
	return (EXIT_SUCCESS);
}
