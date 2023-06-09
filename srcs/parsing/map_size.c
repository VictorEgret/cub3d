#include "cub3d.h"

static bool	is_too_short(const char **content, t_map *map)
{
	int	i;
	int	height;

	i = map->first_line;
	height = 0;
	while (content[i])
	{
		++height;
		++i;
	}
	map->height = height;
	return (height < 3);
}

/*
	Coordinates start at 0:0, map size starts at 1:1
*/
static bool	bad_line(char *line, int line_nb, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_c_in_str(line[i], SPACES) && !ft_c_in_str(line[i], "01"))
		{
			if (!ft_c_in_str(line[i], PLAYER))
				return (error_str("Bad char in map"), true);
			else
			{
				if (map->start_coords[0] != -1)
					return (error_str("Too many players in map"), true);
				map->start_coords[0] = i;
				map->start_coords[1] = line_nb - map->first_line;
				map->start_direction = line[i];
			}
		}
		++i;
	}
	if (i > map->width)
		map->width = i;
	++map->height;
	return (false);
}

static bool	is_line_a_texture(int line_nb, t_map *map)
{
	if (line_nb == map->param_lines[0])
		return (true);
	else if (line_nb == map->param_lines[1])
		return (true);
	else if (line_nb == map->param_lines[2])
		return (true);
	else if (line_nb == map->param_lines[3])
		return (true);
	else if (line_nb == map->param_lines[4])
		return (true);
	else if (line_nb == map->param_lines[5])
		return (true);
	return (false);
}

bool	map_size(t_vars *vars, t_map *map)
{
	const char	**content = (const char **)vars->file_content;
	int			i;

	i = 0;
	while (content[i])
	{
		if (!is_line_a_texture(i, map))
		{
			if (bad_line((char *)content[i], i, map))
				return (false);
			else if (map->first_line == -1 && !is_line_empty(content[i]))
				map->first_line = i;
		}
		++i;
	}
	if (map->first_line == -1)
		return (error_str("No map found"), false);
	if (is_too_short(content, map) || map->width < 3)
		return (error_str("Map too small"), false);
	if (map->start_direction == '\0')
		return (error_str("No start position"), false);
	return (true);
}
