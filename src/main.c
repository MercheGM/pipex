/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/14 19:01:40 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	file[2];
	int	status;

	status = 1;
	if (argc == 5)
	{
		file[I] = ft_openfiles(argv[1], O_RDONLY);
		file[O] = ft_openfiles(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
		status = ft_pipeline(file, argv, envp);
		if (file[O] == -1)
			status = 1;
		ft_closefd(file[I]);
		ft_closefd(file[O]);
	}
	else
		ft_print_help();
	return (status);
}
