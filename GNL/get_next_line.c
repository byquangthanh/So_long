/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:06:12 by sixshooterx       #+#    #+#             */
/*   Updated: 2024/06/24 17:18:44 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*handle_eof_or_error(char *line)
{
	free(line);
	return (NULL);
}

char	*read_from_file(int fd, char *line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*temp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (handle_eof_or_error(line));
		buffer[bytes_read] = '\0';
		if (bytes_read == 0 && *line == '\0')
			return (handle_eof_or_error(line));
		if (bytes_read == 0)
			break ;
		temp = ft_strjoin(line, buffer);
		free(line);
		if (!temp)
			return (NULL);
		line = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

char	*initiliaze_remainder(char *remainder)
{
	if (!remainder)
	{
		remainder = malloc(1);
		if (!remainder)
			return (NULL);
		remainder[0] = '\0';
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*new_line_position;
	char		*temp;

	remainder = initiliaze_remainder(remainder);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_from_file(fd, remainder);
	if (!remainder)
		return (NULL);
	line = split_next_line(remainder);
	new_line_position = ft_strchr(remainder, '\n');
	if (new_line_position)
	{
		temp = ft_strdup(new_line_position + 1);
		free(remainder);
		remainder = temp;
	}
	else
	{
		free(remainder);
		remainder = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int  fd;
// 	char *line;
// 	int  count;

// 	count = 0;
// 	fd = open("example.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break ;
// 		count++;
// 		printf("[%d]:%s\n", count, line);
// 		free(line);
// 		line = NULL;
// 	}
// 	close(fd);
// 	return (0);
// }
