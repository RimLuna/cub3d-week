#include "cub3d.h"

t_dda		init_dda(t_game *game, double ray[2])
{
	t_dda	dda;

	dda.delta_dist[0] = fabs(1.0 / ray[0]);
	dda.delta_dist[1] = fabs(1.0 / ray[1]);
	dda.map_pos[0] = floor(game->pos[0]);
	dda.map_pos[1] = floor(game->pos[1]);
	dda.step[0] = (ray[0] < 0) ? -1 : 1;
	dda.step[1] = (ray[1] < 0) ? -1 : 1;
	dda.side_dist[0] = (ray[0] < 0)
		? (game->pos[0] - dda.map_pos[0]) * dda.delta_dist[0]
		: (dda.map_pos[0] + 1.0 - game->pos[0]) * dda.delta_dist[0];
	dda.side_dist[1] = (ray[1] < 0)
		? (game->pos[1] - dda.map_pos[1]) * dda.delta_dist[1]
		: (dda.map_pos[1] + 1.0 - game->pos[1]) * dda.delta_dist[1];
	return (dda);
}

t_bool		is_hit(t_game *game, t_dda *dda, t_text *text, double ray[2])
{
	if (dda->side_dist[0] < dda->side_dist[1])
	{
		dda->side_dist[0] += dda->delta_dist[0];
		dda->map_pos[0] += dda->step[0];
		text->side = ray[0] > 0 ? N : S;
	}
	else
	{
		dda->side_dist[1] += dda->delta_dist[1];
		dda->map_pos[1] += dda->step[1];
		text->side = ray[1] > 0 ? E : W;
	}
	return (game->map[dda->map_pos[0]][dda->map_pos[1]] == 1);
	
}

void	set_screen_pixel(t_img screen, int i, int j, int color)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)(color >> 16);
	g = (unsigned char)((color % 65536) >> 8);
	b = (unsigned char)(color % 256);
	
	ptr = screen.data + j * screen.size_line + i * (screen.bpp >> 3);
	*ptr = screen.endian ? r : b;
	*(ptr + 1) = g;
	*(ptr + 2) = screen.endian ? b : r;
}

int		get_text_color(t_img tex, double u, double v)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	ptr = tex.data + (int)(v * tex.height) * tex.size_line
		+ (int)(u * tex.width) * (tex.bpp >> 3);
	r = (unsigned char)(tex.endian ? *ptr : *(ptr + 2));
	g = (unsigned char)(*(ptr + 1));
	b = (unsigned char)(tex.endian ? *(ptr + 2) : *ptr);

	return ((r << 16) + (g << 8) + b);
}


void				draw_2(t_game *game, int i, t_text text)
{
	int		color;
	int		start;
	int		end;
	int		j;
	t_img	texture;

	start = game->scr_h / 2 - text.line_height / 2;
	end = game->scr_h / 2 + text.line_height / 2;
	texture = game->textures[text.side];
	j = 0;
	while (j < (start < 0 ? 0 : start))
		set_screen_pixel(game->screen, i, j++, game->color_ceil);
	while (j < (end >= game->scr_h ? game->scr_h - 1 : end))
	{
		color = get_text_color(texture, text.wall_x,
			((j - start) * 1.0) / (end - start));
		set_screen_pixel(game->screen, i, j++, color);
	}
	while (j < game->scr_h)
		set_screen_pixel(game->screen, i, j++, game->color_floor);
}

void		dda_this_shit(t_game *game, int i, double ray[2])
{
	t_dda		dda;
	t_bool		hit;
	t_text		text;

	dda = init_dda(game, ray);

	hit = FALSE;
	while (!hit)
		hit = is_hit(game, &dda, &text, ray);
	text.wall_dist = (text.side == N || text.side == S)
		? (dda.map_pos[0] - game->pos[0] + (1 - dda.step[0]) / 2) / ray[0]
		: (dda.map_pos[1] - game->pos[1] + (1 - dda.step[1]) / 2) / ray[1];
	game->depth_buffer[i] = text.wall_dist;
	text.wall_x = (text.side == N || text.side == S)
		? game->pos[1] + text.wall_dist * ray[1]
		: game->pos[0] + text.wall_dist * ray[0];
	text.wall_x -= floor(text.wall_x);
	text.line_height = (text.wall_dist > 0)
		? game->scr_h / text.wall_dist
		: 2147483647;
	draw_2(game, i, text);
}

void		draw_walls(t_game *game)
{
	double		camera_x;
	double		ray[2];
	int			i;

	i = 0;
	while (i < game->scr_w)
	{
		camera_x = 2.0 * i / game->scr_w - 1;
		ray[0] = game->dir[0] + game->cam_plane[0] * camera_x;
		ray[1] = game->dir[1] + game->cam_plane[1] * camera_x;
		dda_this_shit(game, i++, ray);
	}
}

void		draw(t_game *game)
{
	draw_walls(game);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win,
		game->screen.ptr, 0, 0);
}
