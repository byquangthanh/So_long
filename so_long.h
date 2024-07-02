/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:12:03 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/02 19:58:22 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/include/MLX42/MLX42.h"
# define WIDTH 1280
# define HEIGHT 840

typedef struct s_player
{
	int			x;
	int			y;
	int			move;
	mlx_image_t	*img;
}	t_player;

typedef struct s_data
{
	int			exit;
	int			player;
	int			rows;
	int			cols;
	int			collectible;
	char		**map;
	t_player	player_data;
	mlx_t		*mlx;
}	t_data;

void	load_images(t_data *data);
int		ft_printf(const char *format, ...);
int		handle_close(t_data *data);
int		handle_keypress(int keysym, t_data *data);
void	verify_map(char *filename, t_data *data);
char	*get_next_line(int fd);
int		ft_strlen(const char *s);
void	error_and_exit(char *error_message);
void	free_map_memory(char **map, int rows);
void	game_control(mlx_key_data_t keydata, void *param);
void	initialize_game(t_data *gamedata);

#endif
