#include "cub3d.h"

void	basic_up(t_vars *vars)
{
	t_player	*player;
	t_display	*display;

	vars->display->refresh = true;
	player = vars->player;
	display = vars->display;
	player->x += player->delta_x;
	player->y += player->delta_y;
	player->square_x = player->x / display->square_length;
	player->square_y = player->y / display->square_length;
	return ;
}

void	basic_down(t_vars *vars)
{
	t_player	*player;
	t_display	*display;

	vars->display->refresh = true;
	player = vars->player;
	display = vars->display;
	player->x -= player->delta_x;
	player->y -= player->delta_y;
	player->square_x = player->x / display->square_length;
	player->square_y = player->y / display->square_length;
	return ;
}

void	basic_left(t_vars *vars)
{
	t_player	*player;
	t_display	*display;

	vars->display->refresh = true;
	player = vars->player;
	display = vars->display;
	player->angle -= 0.1;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	player->delta_x = cos(player->angle) * player->speed;
	player->delta_y = sin(player->angle) * player->speed;
	move_player(vars);
	return ;
}

void	basic_right(t_vars *vars)
{
	t_player	*player;
	t_display	*display;

	vars->display->refresh = true;
	player = vars->player;
	display = vars->display;
	player->angle += 0.1;
	if (player->angle > 2 * M_PI)
		player->angle -= 2 * M_PI;
	player->delta_x = cos(player->angle) * player->speed;
	player->delta_y = sin(player->angle) * player->speed;
	return ;
}
