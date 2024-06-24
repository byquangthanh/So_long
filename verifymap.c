/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifymap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:59:54 by quanguye          #+#    #+#             */
/*   Updated: 2024/06/24 17:26:26 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_and_exit(char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	exit(1);
}

int	is_valid_character(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

void	check_walls(char **map, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < cols)
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
			error_and_exit("Map is not surrounded by walls");
		i++;
	}
	while (i < rows)
	{
		if (map[0][i] != '1' || map[cols - 1][i] != '1')
			error_and_exit("Map is not surrounded by walls");
		i++;
	}
}

void	verify_map(char *filename)
{
    int     fd;
    char    *line;
    char    **map;
    int     rows = 0;
    size_t  cols = 0;
    int     collectibles = 0, exits = 0, players = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_and_exit("Unable to open the map file");

    map = (char **)malloc(sizeof(char *) * 1024); // assuming max 1024 lines in the map
    while ((line = get_next_line(fd)) != NULL)
    {
        if (rows == 0)
            cols = strlen(line) - 1; // -1 to ignore the newline character

        if (strlen(line) - 1 != cols)
            error_and_exit("Map is not rectangular");

        for (size_t i = 0; i < cols; i++)
        {
            if (!is_valid_character(line[i]))
                error_and_exit("Map contains invalid characters");
            if (line[i] == 'C') collectibles++;
            if (line[i] == 'E') exits++;
            if (line[i] == 'P') players++;
        }
        map[rows++] = line;
    }
    close(fd);

    if (exits != 1)
        error_and_exit("Map must contain exactly one exit");
    if (collectibles < 1)
        error_and_exit("Map must contain at least one collectible");
    if (players != 1)
        error_and_exit("Map must contain exactly one starting position");

    check_walls(map, rows, cols);
	ft_printf("Looks fine");
    // Free allocated memory for map
    for (int i = 0; i < rows; i++)
        free(map[i]);
    free(map);
}
