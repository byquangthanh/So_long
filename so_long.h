/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:12:03 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/09 18:08:18 by quanguye         ###   ########.fr       */
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
	int	x;
	int	y;
}	t_player;

typedef struct s_collectible
{
	int		x;
	int		y;
	void	*img;
}		t_coll;

typedef struct s_data
{
	int				exit;
	int				rows;
	int				cols;
	int				player_num;
	int				collectible;
	char			**map;
	mlx_t			*mlx;
	int				score;
	mlx_texture_t	*textures[5];
	int				tile_width;
	int				tile_height;
	mlx_image_t		*img;
	t_player		player;
	mlx_image_t		*player_img;
	t_coll			*colls;
	int				coll_count;
	int				total_moves;
	int				row;
	int				col;
}		t_data;

void		load_images(t_data *data);
int			ft_printf(const char *format, ...);
int			handle_close(t_data *data);
int			handle_keypress(int keysym, t_data *data);
void		verify_map(char *filename, t_data *data);
char		*get_next_line(int fd);
int			ft_strlen(const char *s);
void		error_and_exit(char *error_message);
void		free_map_memory(char **map, int rows);
void		initialize_game(t_data *gamedata);
int			is_valid_move(t_data *gamedata, int x, int y);
void		move_player(t_data *gamedata, int new_x, int new_y);
void		handle_key_pressed(t_data *gamedata, int *key_pressed,
				int *new_x, int *new_y);
void		handle_key_release(t_data *gamedata, int *key_pressed);
void		handle_movement(t_data *gamedata, int *new_x,
				int *new_y, int *key_pressed);
void		ft_hook(void *param);
void		initialize_parameters(t_data *gamedata);
void		draw_wall(t_data *gamedata);
void		draw_floor(t_data *gamedata);
void		free_resources(t_data *gamedata);

#endif
