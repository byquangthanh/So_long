/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifymap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:20:45 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/08 16:36:57 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	i = 0;
	while (i < rows)
	{
		if (map[i][0] != '1' || map[i][cols - 1] != '1')
			error_and_exit("Map is not surrounded by walls");
		i++;
	}
}

void	char_checker(char *line, t_data *char_data, int i)
{
	while (i < char_data->cols)
	{
		if (!is_valid_character(line[i]))
			error_and_exit("Map contains invalid characters");
		if (line[i] == 'C')
			char_data->collectible++;
		if (line[i] == 'E')
			char_data->exit++;
		if (line[i] == 'P')
			char_data->player_num++;
		i++;
	}
}

void	iterate_map(char **map, char *filename, t_data *game_data)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_and_exit("Unable to open the map file");
	game_data->collectible = 0;
	game_data->exit = 0;
	game_data->player_num = 0;
	game_data->cols = 0;
	game_data->rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (game_data->rows == 0)
			game_data->cols = ft_strlen(line) - 1;
		if (ft_strlen(line) - 1 != game_data->cols)
			error_and_exit("Map is not rectangular");
		char_checker(line, game_data, 0);
		map[game_data->rows++] = line;
		line = get_next_line(fd);
	}
	close(fd);
}

void	verify_map(char *filename, t_data *data)
{
	data->map = (char **)malloc(sizeof(char *) * 1024);
	iterate_map(data->map, filename, data);
	if (data->exit != 1)
		error_and_exit("Map must contain exactly one exit");
	if (data->collectible < 1)
		error_and_exit("Map must contain at least one collectible");
	if (data->player_num != 1)
		error_and_exit("Map must contain exactly one starting position");
	check_walls(data->map, data->rows, data->cols);
	ft_printf("Looks fine\n");
}
