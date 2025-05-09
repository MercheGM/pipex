/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/09 19:35:32 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	file[2];
	int status;

	status = 1;
	if (argc == 5)
	{
		file[I] = ft_openf(argv[1], O_RDONLY);
		file[O] = ft_openf(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
		status = ft_pipeline(file, argv, envp);
		if ((file[I] == -1) || (file[O] == -1))
			status = 1;
		//ft_printf("----%d-----\n", status);
	}
	else
		ft_print_help();
	return (status);
}
