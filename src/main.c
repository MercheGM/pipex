/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 20:05:13 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/04 18:13:11 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	file[2];

	if (argc == 5)
	{
		file[I] = ft_openf(argv[1], O_RDONLY);
		file[O] = ft_openf(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
		ft_pipeline(file, argv, envp);
	}
	else
		ft_print_help();
	return (EXIT_SUCCESS);
}
