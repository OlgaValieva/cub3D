/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:10:15 by carys             #+#    #+#             */
/*   Updated: 2022/10/12 15:31:37 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	parse_texture(char *line)
{
	t_texture	texture;
	char		*path;
	int			len;

	path = ft_strtrim(line, " ", 0, 0);
	len = ft_strlen(line);
	if (len < 5 || ft_strcmp(line + len - 4, ".xpm"))
	{
		if (path)
			free(path);
		ft_error("use filename extension \".xpm\"\n");
	}
	texture.filename = path;
	return (texture);
}

int	check_number(char **str)
{
	int	color;

	if (!(*str))
		return (-1);
	while (ft_isspace(**str))
		(*str)++;
	color = ft_atoi(*str, 0, -1, 1);
	if (color == -1)
		ft_error("Error on color line!\n");
	if (color < 0 || color > 255)
		ft_error("cub3d: color out of RGB range\n");
	while (ft_isdigit(**str))
		(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == ',' || !(**str))
		(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	return (color);
}

int	parse_color(char *line)
{
	int		color;
	int		r;
	int		g;
	int		b;

	r = check_number(&line);
	g = check_number(&line);
	b = check_number(&line);
	color = (r << 16) + (g << 8) + b;
	return (color);
}

static int	parse_line(char *line, t_data *data, int fd, int i)
{
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
	{
		data->skip++;
		return (data->skip);
	}
	if (line[i] == 'N' && line[i + 1] == 'O')
		data->north_texture = parse_texture(line + i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data->south_texture = parse_texture(line + i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		data->west_texture = parse_texture(line + i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		data->east_texture = parse_texture(line + i + 2);
	else if (line[i] == 'F')
		data->f_color = parse_color(line + i + 1);
	else if (line[i] == 'C')
		data->c_color = parse_color(line + i + 1);
	else
		return (get_x_y(line, data, fd));
	data->skip++;
	return (1);
}

void	parse(char **argv, t_data *d)
{
	int		fd_open;
	char	*line;

	fd_open = open(argv[1], O_RDWR);
	if (fd_open == -1)
		ft_perror("cub3d: file open error");
	while (ft_gnl(&line, fd_open) && parse_line(line, d, fd_open, 0))
		free(line);
	close(fd_open);
	get_map(d, argv[1]);
	check_data(d);
}
