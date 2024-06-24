/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:09:46 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/02/21 15:00:10 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
// void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*split_next_line(char	*str);
char	*ft_strdup(char *s1);
char	*read_from_file(int fd, char *line);
// void	ft_bzero(void *s, size_t n);
#endif
