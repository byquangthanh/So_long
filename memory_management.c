/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:54:35 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/09 18:17:23 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_resources(t_data *gamedata)
{
	int	i;

	i = 0;
	free_map_memory(gamedata->map, gamedata->rows);
	while (i < 5)
	{
		mlx_delete_texture(gamedata->textures[i]);
		i++;
	}
	i = 0;
	// while (i < gamedata->coll_count)
	// {
	// 	mlx_delete_image(gamedata->mlx, gamedata->colls[i].img);
	// 	i++;
	// }
	free(gamedata->colls);
}
