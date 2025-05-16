/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:33:32 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/14 18:50:03 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Print help if the inputs are invalid*/
void	ft_print_help(void)
{
	ft_printf("ERROR: Invalid inputs. Please introduce:\n");
	ft_printf("\t./pipex_bonus infile com1 com2 ... comn outfile\n");
	ft_printf("If you want to use HERE_DOC:\n");
	ft_printf("\t./pipex_bonus here_doc <LIMIT> command1 command2 outfile\n");
	exit (EXIT_FAILURE);
}

/*Function counts number of strings*/
int	ft_count_string(char **string)
{
	int	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}
