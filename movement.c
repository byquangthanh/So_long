/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:15:26 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/09 17:20:00 by quanguye         ###   ########.fr       */
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
	else
	{
		if (!key_pressed)
			handle_key_pressed(gamedata, &key_pressed, &new_x, &new_y);
		else
		{
			if (!mlx_is_key_down(gamedata->mlx, MLX_KEY_W)
				&& !mlx_is_key_down(gamedata->mlx, MLX_KEY_S)
				&& !mlx_is_key_down(gamedata->mlx, MLX_KEY_D)
				&& !mlx_is_key_down(gamedata->mlx, MLX_KEY_A))
				key_pressed = 0;
		}
	}
}

void	handle_key_pressed(t_data *gamedata, int *key_pressed,
				int *new_x, int *new_y)
{
	if (mlx_is_key_down(gamedata->mlx, MLX_KEY_W))
		(*new_x)--;
	else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_S))
		(*new_x)++;
	else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_D))
		(*new_y)++;
	else if (mlx_is_key_down(gamedata->mlx, MLX_KEY_A))
		(*new_y)--;
	else
		return ;
	if (is_valid_move(gamedata, *new_x, *new_y))
	{
		move_player(gamedata, *new_x, *new_y);
		*key_pressed = 1;
	}
}

void	handle_collectible(t_data *gamedata, int new_x, int new_y)
{
	int	i;
	int	j;

	i = 0;
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

void	move_player(t_data *gamedata, int new_x, int new_y)
{
	if (gamedata->map[new_x][new_y] == 'C')
	{
		handle_collectible(gamedata, new_x, new_y);
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
