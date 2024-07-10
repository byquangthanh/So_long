/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:54:35 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/10 14:27:18 by quanguye         ###   ########.fr       */
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
	free_map(gamedata->map, gamedata->rows);
	free(gamedata->colls);
	while (i < 5)
	{
		if (gamedata->textures[i])
			mlx_delete_texture(gamedata->textures[i]);
		i++;
	}
	gamedata->textures[i] = NULL;
}
