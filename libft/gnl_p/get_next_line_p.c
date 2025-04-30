/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:24 by mergarci          #+#    #+#             */
/*   Updated: 2025/04/30 19:10:20 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_p.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			cont;

	cont = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (cont < size)
		ptr[cont++] = '\0';
	return ((void *)ptr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;
	int		i;

	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	i = 0;
	ptr = (char *)ft_calloc_gnl(len_s1 + len_s2 + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (len_s1--)
	{
		ptr[i] = s1[i];
		i++;
	}
	len_s1 = i;
	i = 0;
	while (len_s2--)
		ptr[len_s1++] = s2[i++];
	ptr[len_s1] = '\0';
	return (ptr);
}

char	*ft_memfree(char *ptr)
{
	free(ptr);
	return (NULL);
}

char	*ft_read_gnl(int fd, t_data data, char **str_aux, ssize_t read_bytes)
{
	char		*ptr_aux;
	char		*buffer;

	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (read_bytes > 0 && !data.found_n)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		data.found_n = ft_strchr_gnl(&buffer, str_aux, '\n');
		ptr_aux = data.str_out;
		data.str_out = ft_strjoin_gnl(data.str_out, buffer);
		ptr_aux = ft_memfree_gnl(ptr_aux);
	}
	buffer = ft_memfree_gnl(buffer);
	if ((read_bytes == 0 && ft_strlen_gnl(data.str_out) == 0) || read_bytes < 0)
	{
		*str_aux = ft_memfree_gnl(*str_aux);
		data.str_out = ft_memfree_gnl(data.str_out);
	}
	return (data.str_out);
}

char	*ft_gnl(int fd)
{
	static char	*str_aux;
	t_data		data;
	ssize_t		read_bytes;

	data.found_n = false;
	read_bytes = 1;
	if (fd == -1 || BUFFER_SIZE == 0)
		return (NULL);
	data.str_out = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!data.str_out)
		return (NULL);
	if (!str_aux)
		str_aux = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	else
	{
		ft_strlcpy_gnl(data.str_out, str_aux, ft_strlen_gnl(str_aux) + 1);
		data.found_n = ft_strchr_gnl(&data.str_out, &str_aux, '\n');
	}
	data.str_out = ft_read_gnl(fd, data, &str_aux, read_bytes);
	return (data.str_out);
}
