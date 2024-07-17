/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:25:01 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/16 18:02:35 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_and_exit(char *error_message, t_data *gamedata)
{
	ft_printf("Error:%s\n", error_message);
	if (gamedata)
	{
		if (gamedata->map)
			free_map(gamedata->map, gamedata->rows);
		if (gamedata->temp_map)
			free_map(gamedata->temp_map, gamedata->rows);
		if (gamedata->mlx)
			free_resources(gamedata);
	}
	exit(1);
}

void	initialize_parameters(t_data *gamedata)
{
	gamedata->tile_width = WIDTH / gamedata->cols;
	gamedata->tile_height = HEIGHT / gamedata->rows;
	gamedata->textures[0] = mlx_load_png("assets/floor.png");
	gamedata->textures[1] = mlx_load_png("assets/wall.png");
	gamedata->textures[2] = mlx_load_png("assets/player.png");
	gamedata->textures[3] = mlx_load_png("assets/collectible.png");
	gamedata->textures[4] = mlx_load_png("assets/exit.png");
	gamedata->score = 0;
	gamedata->total_moves = 0;
}

void	draw_floor(t_data *gamedata)
{
	gamedata->row = 0;
	while (gamedata->row < gamedata->rows)
	{
		gamedata->col = 0;
		while (gamedata->col < gamedata->cols)
		{
			gamedata->img = mlx_texture_to_image(gamedata->mlx,
					gamedata->textures[0]);
			mlx_resize_image(gamedata->img, gamedata->tile_width,
				gamedata->tile_height);
			if (!gamedata->img)
				error_and_exit("Failed to convert the img", gamedata);
			mlx_image_to_window(gamedata->mlx, gamedata->img,
				gamedata->col * gamedata->tile_width,
				gamedata->row * gamedata->tile_height);
			gamedata->col++;
		}
		gamedata->row++;
	}
}

void	draw_wall(t_data *gamedata)
{
	gamedata->img = mlx_texture_to_image(gamedata->mlx,
			gamedata->textures[1]);
	mlx_resize_image(gamedata->img, gamedata->tile_width,
		gamedata->tile_height);
	mlx_image_to_window(gamedata->mlx, gamedata->img,
		gamedata->col * gamedata->tile_width,
		gamedata->row * gamedata->tile_height);
}
