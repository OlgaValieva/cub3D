/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:54:41 by carys             #+#    #+#             */
/*   Updated: 2022/10/13 01:44:00 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx/mlx.h"

# define FOV			60
# define GFX_QUALITY    1.0
# define MINIMAP_SIZE   0.2
# define SPEED_MOVE		0.24
# define SPEED_ROTATION	2
# define WALL_DIST		0.25
# define WINDOW_W		1000
# define WINDOW_H		800
# define COLOR "\001\033[1;92m\002"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_size
{
	size_t	x;
	size_t	y;
}	t_size;

typedef struct s_ray
{
	double	distance;
	double	wall_x;
	char	side;
	char	tile;
}	t_ray;

typedef struct s_comp
{
	int		step_x;
	int		step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	ray_dir_x;
	double	ray_dir_y;
}	t_comp;

typedef struct s_texture
{
	char	*filename;
	int		*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*mlx_img_ptr;
}	t_texture;

typedef struct s_data
{
	int			skip;
	int			f_color;
	int			c_color;
	int			mouse;
	int			mouse_delta;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	west_texture;
	t_texture	east_texture;
	size_t		size_x;
	size_t		size_y;
	double		player_x;
	double		player_y;
	double		view_angle;
	char		**map;
	void		*mlx;
	void		*mlx_win;
	void		*img;
}	t_data;

t_ray	ray_cast(t_data d, double angle);
size_t	ft_strlen(const char *str);
bool	ft_isspace(char ch);
double	add_angle(double angle, double add);
double	convert_to_rad(double angle);
char	*ft_strtrim(char *s1, char *set, int flag, size_t i);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);
int		ft_gnl(char **line, int fd);
int		ft_atoi(const char *str, int i, int flag, int m);
int		ft_strcmp(const char *s1, const char *s2);
int		get_x_y(char *str, t_data *d, int fd);
int		red_cross(t_data *d);
int		keys(int key, t_data *d);
int		mouse(int x, int y, t_data *d);
void	ft_putstr_fd(char *s, int fd);
void	ft_error(char *str);
void	ft_perror(char *str);
void	parse(char **argv, t_data *d);
void	get_map(t_data *d, char *filename);
void	check_data(t_data *d);
void	check_walls(t_data *d, size_t x, size_t y);
void	check_forbidden_char(t_data *d, size_t x, size_t y);
void	check_space(t_data *d, size_t x, size_t y);
void	images(t_data *d);
void	turn_left(t_data *d);
void	turn_right(t_data *d);
void	step_forward(t_data *d);
void	step_back(t_data *d);
void	step_left(t_data *d);
void	step_right(t_data *d);
void	paint_window(t_data *d);
void	draw_minimap(t_data d);
void	wall(t_data data, t_ray ray, int x);
void	draw_vertical(t_data data, int x, int width, int height);
void	image_pixel_put(t_data data, int x, int y, unsigned int color);
void	error_free(char *str, t_data *d);
void	all_free(t_data *d);
void	game_end(t_data *d);

#endif