/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/07 19:00:25 by mergarci         ###   ########.fr       */
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
		status = ft_pipeline(file, argv, envp, &status);
		ft_printf("----%d-----", status);
	}
	else
		ft_print_help();
	return (status);
}
