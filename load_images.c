/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:32:37 by quanguye          #+#    #+#             */
/*   Updated: 2024/06/24 14:42:36 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_data *data)
{
	int	width;
	int	height;

	data->player_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/player.xpm", &width, &height);
	data->wall_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/wall.xpm", &width, &height);
	data->floor_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/floor.xpm", &width, &height);
	data->collectible_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/collectible.xpm", &width, &height);
	data->exit_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"assets/exit.xpm", &width, &height);
}
