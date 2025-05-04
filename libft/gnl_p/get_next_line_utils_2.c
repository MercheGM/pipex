/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:20:06 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/04 19:25:24 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_p.h"

/* Functions lexicographically compare the null-terminated strings s1 and s2.*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (uc_s1[i] != '\0' && uc_s2[i] != '\0' && i < n)
	{
		if ((uc_s1[i] != uc_s2[i]))
			return (uc_s1[i] - uc_s2[i]);
		i++;
	}
	if (i == n)
		i--;
	return (uc_s1[i] - uc_s2[i]);
}
