#include "cub3d.h"

static void	start_direction(t_vars *vars)
{
	const t_map	*map = vars->map;
	
	if (map->start_direction == 'N')
		vars->player->angle = PI / 2;
	else if (map->start_direction == 'S')
		vars->player->angle = 3 * PI / 2;
	else if (map->start_direction == 'W')
		vars->player->angle = PI;
	else
		vars->player->angle = 0; //FIXME Starting at 0 create a problem where the first rays points at 0;0
}

/*
	File opener
	Fills vars->file_content with the content of the map file.
	Returns true on success and false if error
*/
bool	file_opener(char *file_name, t_vars *vars)
{
	int		fd;
	int		i;
	int		lines;
	char	buff[1];
	char	**content;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (perror("open"), false);
	lines = 1;
	while (read(fd, buff, 1))
		lines += (buff[0] == '\n' || buff[0] == '\0');
	close(fd);
	content = malloc(sizeof (char *) * (lines + 1));
	if (!content)
		return (perror("malloc"), false);
	content[lines] = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_free_strs(content), perror("open"), false);
	i = 0;
	while (i < lines)
		content[i++] = get_next_line(fd);
	vars->file_content = content;
	return (close(fd), true);
}

/*
	TODO 
	Fill map->isles (contains the number of individual islands)
		is init to -1, if at the end is 1 then set it to 0
		islands are 1s separated by lines full of 1
		Do the same for the islands separated by a column of 1
	TODO
		Check if the RGB Codes are correct (no missing)
*/

bool	parsing(char *file_name, t_vars *vars, t_map *map)
{
	if (ft_strncmp(".cub", file_name + ft_strlen(file_name) - 4, 4) != 0)
		return (error_str("Wrong file format"), false);
	if (file_opener(file_name, vars) == false)
		return (false);
	show_file(vars);
	if (get_textures_info(vars, map) == false)
		return (false);
	show_texture_info(map);
	if (map_size(vars, map) == false)
		return (false);
	show_map_info(map);
	if (create_map(vars, map) == false)
		return (false);
	if (map_correct(map) == false)
		return (false);
	format_map(map);
	count_islands(map);
	ft_printf("Islands %d /Islands\n", map->islands);
	show_map(map);
	vars->player->x = map->start_coords[0];
	vars->player->y = map->start_coords[1];
	vars->player->square_x = map->start_coords[0];
	vars->player->square_y = map->start_coords[1];
	start_direction(vars);
	return (true);
}
