/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:58:42 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/08 19:13:43 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_hook(void *param)
{
	t_data		*gamedata;
	int			new_x;
	int			new_y;
	static int	key_pressed;

	if (key_pressed != 0 && key_pressed != 1)
		key_pressed = 0;
	gamedata = (t_data *)param;
	new_x = gamedata->player.x;
	new_y = gamedata->player.y;
	if (mlx_is_key_down(gamedata->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gamedata->mlx);
	else if (!key_pressed)
	{
		if (mlx_is_key_down(gamedata->mlx, MLX_KEY_W))
			new_x--;
		else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_S))
			new_x++;
		else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_D))
			new_y++;
		else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_A))
			new_y--;
		else
			return ;
		if (is_valid_move(gamedata, new_x, new_y))
		{
			move_player(gamedata, new_x, new_y);
			key_pressed = 1;
		}
	}
	else if (!mlx_is_key_down(gamedata->mlx, MLX_KEY_W)
		&& !mlx_is_key_down(gamedata->mlx, MLX_KEY_S)
		&& !mlx_is_key_down(gamedata->mlx, MLX_KEY_D)
		&& !mlx_is_key_down(gamedata->mlx, MLX_KEY_A))
		key_pressed = 0;
}

void	move_player(t_data *gamedata, int new_x, int new_y)
{
	int	i;
	int	j;

	i = 0;
	if (gamedata->map[new_x][new_y] == 'C')
	{
		gamedata->score++;
		gamedata->map[new_x][new_y] = '0';
		while (i < gamedata->coll_count)
		{
			if (gamedata->colls[i].x == new_x
				&& gamedata->colls[i].y == new_y)
			{
				mlx_delete_image(gamedata->mlx, gamedata->colls[i].img);
				j = i;
				while (j < gamedata->coll_count - 1)
				{
					gamedata->colls[j] = gamedata->colls[j + 1];
					j++;
				}
				gamedata->coll_count--;
				break ;
			}
			i++;
		}

		ft_printf("Score: %d\n", gamedata->score);
	}
	else if (gamedata->map[new_x][new_y] == 'E'
		&& gamedata->score == gamedata->collectible)
	{
		ft_printf("Good job you won.");
		exit(1);
	}
	gamedata->total_moves++;
	gamedata->player.x = new_x;
	gamedata->player.y = new_y;
	gamedata->player_img->instances[0].x = new_y * gamedata->tile_width;
	gamedata->player_img->instances[0].y = new_x * gamedata->tile_height;
	ft_printf("Total moves: %d\n", gamedata->total_moves);
}


int	is_valid_move(t_data *gamedata, int x, int y)
{
	if (x < 0 || x >= gamedata->rows || y < 0 || y >= gamedata->cols)
		return (0);

	if (gamedata->map[x][y] == '1')
		return (0);

	return (1);
}

void	initialize_game(t_data *gamedata)
{
	gamedata->mlx = mlx_init(WIDTH, HEIGHT, "So Long", true);
	if (!gamedata->mlx)
		error_and_exit("Unable to initialize mlx");

	gamedata->tile_width = WIDTH / gamedata->cols;
	gamedata->tile_height = HEIGHT / gamedata->rows;

	ft_printf("%d\n", gamedata->cols);
	ft_printf("%d\n", gamedata->rows);
	ft_printf("%d\n", gamedata->tile_width);
	ft_printf("%d", gamedata->tile_height);

	gamedata->textures[0] = mlx_load_png("assets/floor.png");
	gamedata->textures[1] = mlx_load_png("assets/wall.png");
	gamedata->textures[2] = mlx_load_png("assets/player.png");
	gamedata->textures[3] = mlx_load_png("assets/collectible.png");
	gamedata->textures[4] = mlx_load_png("assets/exit.png");

	gamedata->score = 0;
	gamedata->total_moves = 0;

	int	row;
	int	col;

	col = 0;
	row = 0;
	while (row < gamedata->rows)
	{
		col = 0;
		while (col < gamedata->cols)
		{
			gamedata->img = mlx_texture_to_image(gamedata->mlx,
					gamedata->textures[0]);
			mlx_resize_image(gamedata->img, gamedata->tile_width,
				gamedata->tile_height);
			if (!gamedata->img)
				error_and_exit("Failed to convert the img");
			mlx_image_to_window(gamedata->mlx, gamedata->img,
				col * gamedata->tile_width, row * gamedata->tile_height);
			col++;
		}
		row++;
	}
	row = 0;
	gamedata->coll_count = 0;
	gamedata->colls = malloc(gamedata->collectible * sizeof(t_coll));
	if (!gamedata->colls)
		error_and_exit("Failed to allocate memory for colls");
	row = 0;
	while (row < gamedata->rows)
	{
		col = 0;
		while (col < gamedata->cols)
		{
			if (gamedata->map[row][col] == '1')
			{
				gamedata->img = mlx_texture_to_image(gamedata->mlx,
						gamedata->textures[1]);
				mlx_resize_image(gamedata->img, gamedata->tile_width,
					gamedata->tile_height);
				mlx_image_to_window(gamedata->mlx, gamedata->img,
					col * gamedata->tile_width, row * gamedata->tile_height);
			}
			else if (gamedata->map[row][col] == 'C')
			{
				gamedata->colls[gamedata->coll_count].x = row;
				gamedata->colls[gamedata->coll_count].y = col;
				gamedata->colls[gamedata->coll_count].img
					= mlx_texture_to_image(gamedata->mlx,
						gamedata->textures[3]);
				mlx_resize_image(gamedata->colls[gamedata->coll_count].img,
					gamedata->tile_width, gamedata->tile_height);
				mlx_image_to_window(gamedata->mlx,
					gamedata->colls[gamedata->coll_count].img,
					col * gamedata->tile_width, row * gamedata->tile_height);
				gamedata->coll_count++;
			}
			else if (gamedata->map[row][col] == 'E')
			{
				gamedata->img = mlx_texture_to_image(gamedata->mlx,
						gamedata->textures[4]);
				mlx_resize_image(gamedata->img, gamedata->tile_width,
					gamedata->tile_height);
				mlx_image_to_window(gamedata->mlx, gamedata->img,
					col * gamedata->tile_width, row * gamedata->tile_height);
			}
			col++;
		}
		row++;
	}
	row = 0;
	while (row < gamedata->rows)
	{
		col = 0;
		while (col < gamedata->cols)
		{
			if (gamedata->map[row][col] == 'P')
			{
				gamedata->player_img = mlx_texture_to_image(gamedata->mlx,
						gamedata->textures[2]);
				mlx_resize_image(gamedata->player_img,
					gamedata->tile_width, gamedata->tile_height);
				mlx_image_to_window(gamedata->mlx, gamedata->player_img,
					col * gamedata->tile_width, row * gamedata->tile_height);
				gamedata->player.x = row;
				gamedata->player.y = col;
				col++;
				continue ;
			}
			else
				col++;
		}
		row++;
	}
	mlx_loop_hook(gamedata->mlx, &ft_hook, gamedata);
	mlx_loop(gamedata->mlx);
	mlx_terminate(gamedata->mlx);
}
