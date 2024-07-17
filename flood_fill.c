/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:06:44 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/17 16:13:19 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_coordination(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	while (i < data->rows)
	{
		y = 0;
		while (data->map[i][y] != '\0')
		{
			if (data->map[i][y] == 'P')
			{
				data->player.x = i;
				data->player.y = y;
				return ;
			}
			y++;
		}
		i++;
	}
}

void	check_valid_map(t_data *data)
{
	int		i;
	int		y;

	data->temp_collectible = 0;
	data->temp_exit = 0;
	i = 0;
	data->temp_map = malloc(sizeof(char *) * data->rows);
	while (i < data->rows)
	{
		data->temp_map[i] = malloc(sizeof(char) * (data->cols + 1));
		y = 0;
		while (y < data->cols)
		{
			data->temp_map[i][y] = data->map[i][y];
			y++;
		}
		data->temp_map[i][y] = '\0';
		i++;
	}
	flood_fill(data->temp_map, data->player.x, data->player.y, data);
	i = 0;
	if (data->temp_collectible != data->collectible)
		error_and_exit("Collectibles are not reachable", data);
	if (data->temp_exit != 1)
		error_and_exit("Exit is not reachable", data);
}

void	flood_fill(char **map, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || map[x] == NULL || map[x][y] == '\0'
		|| map[x][y] == '1')
		return ;
	if (map[x][y] == 'C')
		(data->temp_collectible)++;
	if (map[x][y] == 'E')
		(data->temp_exit)++;
	map[x][y] = '1';
	flood_fill(map, x - 1, y, data);
	flood_fill(map, x + 1, y, data);
	flood_fill(map, x, y - 1, data);
	flood_fill(map, x, y + 1, data);
}

void	cleanup_gnl(void)
{
	get_next_line(-1);
}
