/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:50:49 by lgertrud          #+#    #+#             */
/*   Updated: 2025/08/23 14:59:00 by ghenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_join_free(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s, size_t n);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);

#endif
