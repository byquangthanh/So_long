/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:58:42 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/10 15:15:07 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_collectible(t_data *gamedata)
{
	gamedata->colls[gamedata->coll_count].x = gamedata->row;
	gamedata->colls[gamedata->coll_count].y = gamedata->col;
	gamedata->colls[gamedata->coll_count].img
		= mlx_texture_to_image(gamedata->mlx,
			gamedata->textures[3]);
	mlx_resize_image(gamedata->colls[gamedata->coll_count].img,
		gamedata->tile_width, gamedata->tile_height);
	mlx_image_to_window(gamedata->mlx,
		gamedata->colls[gamedata->coll_count].img,
		gamedata->col * gamedata->tile_width,
		gamedata->row * gamedata->tile_height);
	gamedata->coll_count++;
}

void	draw_exit(t_data *gamedata)
{
	gamedata->img = mlx_texture_to_image(gamedata->mlx,
			gamedata->textures[4]);
	mlx_resize_image(gamedata->img, gamedata->tile_width,
		gamedata->tile_height);
	mlx_image_to_window(gamedata->mlx, gamedata->img,
		gamedata->col * gamedata->tile_width,
		gamedata->row * gamedata->tile_height);
}

void	draw_textures(t_data *gamedata)
{
	gamedata->coll_count = 0;
	gamedata->colls = malloc(gamedata->collectible * sizeof(t_coll));
	if (!gamedata->colls)
		error_and_exit("Failed to allocate memory for collectibles", gamedata);
	gamedata->row = 0;
	while (gamedata->row < gamedata->rows)
	{
		gamedata->col = 0;
		while (gamedata->col < gamedata->cols)
		{
			if (gamedata->map[gamedata->row][gamedata->col] == '1')
				draw_wall(gamedata);
			else if (gamedata->map[gamedata->row][gamedata->col] == 'C')
				draw_collectible(gamedata);
			else if (gamedata->map[gamedata->row][gamedata->col] == 'E')
				draw_exit(gamedata);
			gamedata->col++;
		}
		gamedata->row++;
	}
}

void	draw_player(t_data *gamedata)
{
	gamedata->row = 0;
	while (gamedata->row < gamedata->rows)
	{
		gamedata->col = 0;
		while (gamedata->col < gamedata->cols)
		{
			if (gamedata->map[gamedata->row][gamedata->col] == 'P')
			{
				gamedata->player_img = mlx_texture_to_image(gamedata->mlx,
						gamedata->textures[2]);
				mlx_resize_image(gamedata->player_img,
					gamedata->tile_width, gamedata->tile_height);
				mlx_image_to_window(gamedata->mlx, gamedata->player_img,
					gamedata->col * gamedata->tile_width,
					gamedata->row * gamedata->tile_height);
				gamedata->player.x = gamedata->row;
				gamedata->player.y = gamedata->col;
				gamedata->col++;
			}
			else
				gamedata->col++;
		}
		gamedata->row++;
	}
}

void	initialize_game(t_data *gamedata)
{
	gamedata->mlx = mlx_init(WIDTH, HEIGHT, "So Long", true);
	if (!gamedata->mlx)
		error_and_exit("Unable to initialize mlx", gamedata);
	initialize_parameters(gamedata);
	draw_floor(gamedata);
	draw_textures(gamedata);
	draw_player(gamedata);
	mlx_loop_hook(gamedata->mlx, &ft_hook, gamedata);
	mlx_loop(gamedata->mlx);
	mlx_terminate(gamedata->mlx);
	free_resources(gamedata);
}
