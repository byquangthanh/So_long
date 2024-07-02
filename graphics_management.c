/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:41:52 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/02 20:03:55 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook(void *param)
{
	t_data		*gamedata;
	t_player	*player;

	gamedata = (t_data *)param;
	player = &(gamedata->player_data);
	if (mlx_is_key_down(gamedata->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gamedata->mlx);

	int new_x = player->x;
	int new_y = player->y;

	if (mlx_is_key_down(gamedata->mlx, MLX_KEY_W) && player->move == 0)
	{
		new_y--;
		player->move = 1;
	}
	else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_S) && player->move == 0)
	{
		new_y++;
		player->move = 1;
	}
	else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_A) && player->move == 0)
	{
		new_x--;
		player->move = 1;
	}
	else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_D) && player->move == 0)
	{
		new_x++;
		player->move = 1;
	}

	if (!mlx_is_key_down(gamedata->mlx, MLX_KEY_W) &&
		!mlx_is_key_down(gamedata->mlx, MLX_KEY_S) &&
		!mlx_is_key_down(gamedata->mlx, MLX_KEY_A) &&
		!mlx_is_key_down(gamedata->mlx, MLX_KEY_D))
	{
		player->move = 0;
	}

	if (new_x >= 0 && new_x < gamedata->cols && new_y >= 0 && new_y < gamedata->rows &&
		gamedata->map[new_y][new_x] != '1')
	{
		printf("Player new position: (%d, %d)\n", new_x, new_y);
		printf("Player current position: (%d, %d)\n", player->x, player->y);

		// Update player position in the map
		gamedata->map[player->y][player->x] = '0';
		gamedata->map[new_y][new_x] = 'P';
		player->x = new_x;
		player->y = new_y;

		// Update player image position
		player->img->instances[0].x = player->x * (WIDTH / gamedata->cols);
		player->img->instances[0].y = player->y * (HEIGHT / gamedata->rows);

		// Debug: Print the new image position
		printf("Player image new position: (%d, %d)\n", player->img->instances[0].x, player->img->instances[0].y);
	}
	else
	{
		// Debug: If the move is invalid, print a message
		printf("Invalid move to position: (%d, %d)\n", new_x, new_y);
	}
}


void	initialize_game(t_data *gamedata)
{
	int			i = 0;
	int			j;
	int			tile_width;
	int			tile_height;
	mlx_image_t	*img;
	mlx_texture_t *textures[5];
	mlx_image_t *images[gamedata->rows][gamedata->cols];

	gamedata->mlx = mlx_init(WIDTH, HEIGHT, "So Long", true);
	if (!gamedata->mlx)
		error_and_exit("Failed to initialize MLX42");

	textures[0] = mlx_load_png("assets/floor.png");
	textures[1] = mlx_load_png("assets/wall.png");
	textures[2] = mlx_load_png("assets/player.png");
	textures[3] = mlx_load_png("assets/collectible.png");
	textures[4] = mlx_load_png("assets/exit.png");
	for (int k = 0; k < 5; k++) {
		if (!textures[k])
			error_and_exit("Failed to load one of the textures");
	}

	tile_width = WIDTH / gamedata->cols;
	tile_height = HEIGHT / gamedata->rows;

	while (i < gamedata->rows)
	{
		j = 0;
		while (j < gamedata->cols)
		{
			int x = j * tile_width;
			int y = i * tile_height;
			if (gamedata->map[i][j] == '1')
				img = mlx_texture_to_image(gamedata->mlx, textures[1]); // Wall texture should be index 1
			else if(gamedata->map[i][j] == '0')
				img = mlx_texture_to_image(gamedata->mlx, textures[0]); // Floor texture should be index 0
			else if(gamedata->map[i][j] == 'P') {
				img = mlx_texture_to_image(gamedata->mlx, textures[2]);
				gamedata->player_data.x = j;
				gamedata->player_data.y = i;
				gamedata->player_data.img = img;
				gamedata->player_data.move = 0; // Initialize move flag
			}
			else if(gamedata->map[i][j] == 'C')
				img = mlx_texture_to_image(gamedata->mlx, textures[3]);
			else if(gamedata->map[i][j] == 'E')
				img = mlx_texture_to_image(gamedata->mlx, textures[4]);

			mlx_resize_image(img, tile_width, tile_height);

			if (!img)
				error_and_exit("Failed to convert texture to image");

			if (mlx_image_to_window(gamedata->mlx, img, x, y) == -1)
				error_and_exit("Failed to put image to window");

			images[i][j] = img;
			j++;
		}
		i++;
	}

	mlx_loop_hook(gamedata->mlx, &hook, gamedata);
	mlx_loop(gamedata->mlx);
	for (int k = 0; k < 5; k++) {
		mlx_delete_texture(textures[k]);
	}
	mlx_terminate(gamedata->mlx);
}
