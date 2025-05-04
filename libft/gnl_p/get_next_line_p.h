/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_p.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:18 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/04 19:22:04 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_P_H
# define GET_NEXT_LINE_P_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct data
{
	char	*str_out;
	bool	found_n;
}	t_data;

// GNL
void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_memfree_gnl(char *ptr);
char	*ft_read_gnl(int fd, t_data data, char **str_aux, ssize_t read_bytes);
char	*ft_gnl(int fd, char *limit);

//GNL_UTILS
char	*ft_strdup_gnl(const char *s1);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen_gnl(const char *s);
char	*ft_substr_gnl(char const *s, unsigned int star, size_t len);
bool	ft_strchr_gnl(char **s, char **dst, int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif