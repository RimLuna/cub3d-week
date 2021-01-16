#include "cub3d.h"
#include <stdio.h>

int			lookupColor[] =
{
	0xFFF5CC,
	0xBB0055
};

t_dda		init_dda(t_game *game, double ray[2])
{
	t_dda	ddata;

	ddata.delta_dist[0] = fabs(1.0 / ray[0]);
	ddata.delta_dist[1] = fabs(1.0 / ray[1]);
	if (ray[0] * ray[1] == 0)
		printf("%f %f\n", ddata.delta_dist[0], ddata.delta_dist[1]);
	ddata.map_pos[0] = floor(game->pos[0]);
	ddata.map_pos[1] = floor(game->pos[1]);
	ddata.step[0] = (ray[0] < 0) ? -1 : 1;
	ddata.step[1] = (ray[1] < 0) ? -1 : 1;
	ddata.side_dist[0] = (ray[0] < 0)
		? (game->pos[0] - ddata.map_pos[0]) * ddata.delta_dist[0]
		: (ddata.map_pos[0] + 1.0 - game->pos[0]) * ddata.delta_dist[0];
	ddata.side_dist[1] = (ray[1] < 0)
		? (game->pos[1] - ddata.map_pos[1]) * ddata.delta_dist[1]
		: (ddata.map_pos[1] + 1.0 - game->pos[1]) * ddata.delta_dist[1];
	return (ddata);
}

t_bool		is_hit(t_game *game, t_dda *ddata, double ray[2])
{
	t_bool		hit;

	hit = FALSE;
	if (ddata->side_dist[0] < ddata->side_dist[1])
	{
		ddata->side_dist[0] += ddata->delta_dist[0];
		ddata->map_pos[0] += ddata->step[0];
		ddata->side = 0;
	}
	else
	{
		ddata->side_dist[1] += ddata->delta_dist[1];
		ddata->map_pos[1] += ddata->step[1];
		ddata->side = 1;
	}
	return ((t_bool)(game->map[ddata->map_pos[0]][ddata->map_pos[1]] == 1));
}

void		put_it(t_img screen, int i, int j, int color)
{

}

void		draw_line(double start, double end, int x, t_game *game, int color)
{
	int		j;

	start = start < 0 ? 0 : start;
	end = end >= game->scr_h ? game->scr_h - 1 : end;
	j = 0;
	while (j < start)
		put_it(game->screen, x, j++, game->color_ceil);
	while (j < end)
		put_it(game->screen, x, j++, color);
	while (j < game->scr_h)
		put_it(game->screen, x, j++, game->color_floor);
}

void		dda(t_game *game, double ray[2], int i)
{
	t_bool		hit;
	t_dda		ddata;

	hit = FALSE;
	ddata = init_dda(game, ray);
	while (!hit)
		hit = is_hit(game, &ddata, ray);
	ddata.wall_dist = ddata.side == 0
		? (ddata.map_pos[0] - game->pos[0] + (1 - ddata.step[0]) / 2) / ray[0]
		: (ddata.map_pos[1] - game->pos[1] + (1 - ddata.step[1]) / 2) / ray[1];
	game->depth_buffer[i] = ddata.wall_dist;
	ddata.line_height = game->scr_h / ddata.wall_dist;

	int		start;
	int		end;

	start = -ddata.line_height / 2 + game->scr_h / 2;
	start = start < 0 ? 0 : start;
	end = ddata.line_height / 2 + game->scr_h / 2;
	end = end >= game->scr_h ? game->scr_h - 1 : end;
	int		color;
	color = lookupColor[game->map[ddata.map_pos[0]][ddata.map_pos[0]]];
	color = ddata.side ? color / 2 : color;
	draw_line(start, end, i, game, color);
}

void		camera(t_game *game)
{
	double		camera_x;
	int			i;
	double		ray[2];

	i = 0;
	while (i < game->scr_w)
	{
		camera_x = 2.0 * i / game->scr_w - 1;
		ray[0] = game->dir[0] + game->cam_plane[0] * camera_x;
		ray[1] = game->dir[1] + game->cam_plane[1] * camera_x;
		printf("cam_x: %f i:%d Rx:%f Ry:%f\n", camera_x, i, ray[0], ray[1]);
		dda(game, ray, i);
		i++;
	}
}

int			main(int ac, char **av)
{
	t_game		*game;
	if (!(game = game_init(ac, av)))
		return (ERROR);
	camera(game);
	quit(game, SUCCESS);
	return (SUCCESS);
}
