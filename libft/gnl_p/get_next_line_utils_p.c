/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_p.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:53 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/06 19:09:57 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_p.h"

char	*ft_strdup_gnl(const char *s1)
{
	char	*ptr;
	size_t	len;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen_gnl(s1);
	ptr = (char *)ft_calloc_gnl(len + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen_gnl(src));
	else
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		if (i < ft_strlen_gnl(src))
			return (ft_strlen_gnl(src));
	}
	return (i);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	cont;

	cont = 0;
	while (s[cont] != '\0')
		cont++;
	return (cont);
}

char	*ft_substr_gnl(char const *s, unsigned int star, size_t len)
{
	char			*ptr;
	unsigned int	len_src;

	if (!s)
		return (NULL);
	len_src = (unsigned int)ft_strlen_gnl(s);
	if (len > len_src)
		len = len_src - star;
	if (len_src < star || len_src == 0)
		return (ft_strdup_gnl(""));
	if (star + len == len_src + 1)
		len--;
	ptr = (char *)ft_calloc_gnl(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	if ((star < len || (star + len) <= len_src + 1))
	{
		while (star--)
			s++;
		ft_strlcpy_gnl(ptr, s, len + 1);
		return (ptr);
	}
	return (ptr);
}

bool	ft_strchr_gnl(char **s, char **dst, int c)
{
	char	*ptr_aux;
	int		cont;

	ptr_aux = *s;
	cont = 0;
	while (ptr_aux[cont] != '\0' && ptr_aux[cont] != (unsigned char)c)
		cont++;
	if (*dst != NULL)
		*dst = ft_memfree_gnl(*dst);
	if (ptr_aux[cont] == '\0')
	{
		*dst = NULL;
		return (false);
	}
	else
	{
		*s = ft_substr_gnl(*s, 0, ++cont);
		*dst = ft_strdup_gnl(&ptr_aux[cont]);
		ptr_aux = ft_memfree_gnl(ptr_aux);
	}
	return (true);
}
