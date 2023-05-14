#include "cub3d.h"

void	draw_2d(t_display *display, t_map *map, t_player *player)
{
	const int	square_length = biggest(display->heigth, display->width)
		/ biggest(map->heigth, map->width);
	int			i;
	int			j;
	int			x;
	int			y;

	i = 0;
	y = 0;
	ft_printf("Display Heigth %d\n", display->heigth);
	ft_printf("Display Width %d\n", display->width);
	ft_printf("Line %s /Line\n", map->map[map->heigth - 1]);
	ft_printf("Square Length %d /Square Length\n", square_length);
	player->x = player->x * square_length - square_length / 2;
	player->y = player->y * square_length - square_length / 2;
	while (i < display->heigth)
	{
		j = 0;
		x = 0;
		while (j < display->width)
		{
			if (!map->map[y] || !map->map[y][x])
				break ;
			if (map->map[y] && ft_c_in_str(map->map[y][x], FREE))
				mlx_spp(display, j, i, 0xFF00FF);
			else
				mlx_spp(display, j, i, 0x00FF00);
			if (j > x * square_length && x < map->width - 1)
				mlx_spp(display, j, i, 0);
			if (i > y * square_length && y < map->heigth - 1)
				mlx_spp(display, j, i, 0);
			if (j > x * square_length && x < map->width - 1)
				++x;
			++j;
		}
		if (i > y * square_length && y < map->heigth - 1)
			++y;
		++i;
	}
	mlx_spp(display, player->x, player->y, 0xFFFFFF);
	mlx_spp(display, player->x - 1, player->y, 0xFFFFFF);
	mlx_spp(display, player->x + 1, player->y, 0xFFFFFF);
	mlx_spp(display, player->x, player->y - 1, 0xFFFFFF);
	mlx_spp(display, player->x, player->y + 1, 0xFFFFFF);
	mlx_put_image_to_window(display->mlx, display->win, display->img, -2, -2);
}


