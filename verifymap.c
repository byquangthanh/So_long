/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifymap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:20:45 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/17 16:09:32 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_character(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

void	check_walls(t_data *gamedata, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < cols)
	{
		if (gamedata->map[0][i] != '1' || gamedata->map[rows - 1][i] != '1')
			error_and_exit("Map is not surrounded by walls", gamedata);
		i++;
	}
	i = 0;
	while (i < rows)
	{
		if (gamedata->map[i][0] != '1' || gamedata->map[i][cols - 1] != '1')
			error_and_exit("Map is not surrounded by walls", gamedata);
		i++;
	}
}

void	char_checker(char *line, t_data *char_data)
{
	int	i;

	i = 0;
	while (i < char_data->cols)
	{
		if (!is_valid_character(line[i]))
			error_and_exit("Map contains invalid characters", char_data);
		if (line[i] == 'C')
			char_data->collectible++;
		if (line[i] == 'E')
			char_data->exit++;
		if (line[i] == 'P')
			char_data->player_num++;
		i++;
	}
}

void	iterate_map(char *filename, t_data *gamedata)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_and_exit("Unable to open the map file", gamedata);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (gamedata->rows == 0)
			gamedata->cols = ft_strlen(line) - 1;
		if (ft_strlen(line) - 1 != gamedata->cols)
		{
			free(line);
			cleanup_gnl();
			error_and_exit("Map is not rectangular", gamedata);
		}
		char_checker(line, gamedata);
		gamedata->map[gamedata->rows++] = line;
		line = get_next_line(fd);
	}
	close(fd);
}

void	verify_map(char *filename, t_data *data)
{
	data->cols = 0;
	data->rows = 0;
	data->exit = 0;
	data->collectible = 0;
	data->player_num = 0;
	data->map = (char **)malloc(sizeof(char *) * 1024);
	data->temp_map = NULL;
	data->mlx = NULL;
	iterate_map(filename, data);
	get_player_coordination(data);
	if (data->exit != 1)
		error_and_exit("Map must contain exactly one exit", data);
	if (data->collectible < 1)
		error_and_exit("Map must contain at least one collectible", data);
	if (data->player_num != 1)
		error_and_exit("Map must contain exactly one player", data);
	check_walls(data, data->rows, data->cols);
	check_valid_map(data);
	ft_printf("Looks fine\n");
}
