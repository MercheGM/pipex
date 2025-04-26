/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/26 13:42:43 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	infile;
	int	outf;

	if (argc >= 5)
	{
		if (argc == 6 && !ft_strncmp(argv[1], "here_doc", 8))
		{
			infile = ft_openfile("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC);
			outf = ft_openfile(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND);
			ft_heredoc(infile, outf, argv[2], argv);
			exit (EXIT_SUCCESS);
		}
		else
		{
			infile = ft_openfile(argv[1], O_RDONLY);
			outf = ft_openfile(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
			ft_pipeline(infile, outf, argv, envp);
		}
	}
	else
	{
		ft_print_help();
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
