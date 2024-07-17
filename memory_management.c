/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:54:35 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/17 16:12:46 by quanguye         ###   ########.fr       */
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
	if (gamedata->map)
		free_map(gamedata->map, gamedata->rows);
	if (gamedata->temp_map)
		free_map(gamedata->temp_map, gamedata->rows);
	if (gamedata->colls)
		free(gamedata->colls);
	while (i < 5)
	{
		if (gamedata->textures[i])
			mlx_delete_texture(gamedata->textures[i]);
		i++;
	}
	gamedata->textures[i] = NULL;
}
