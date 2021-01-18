#include "cub3d.h"

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

t_bool		is_hit(t_game *game, t_dda *ddata, t_text *texture, double ray[2])
{
	t_bool		hit;

	hit = FALSE;
	if (ddata->side_dist[0] < ddata->side_dist[1])
	{
		ddata->side_dist[0] += ddata->delta_dist[0];
		ddata->map_pos[0] += ddata->step[0];
		texture->side = ray[0] > 0 ? N : S;
	}
	else
	{
		ddata->side_dist[1] += ddata->delta_dist[1];
		ddata->map_pos[1] += ddata->step[1];
		texture->side = ray[1] > 0 ? E : W;
	}
	return (game->map[ddata->map_pos[0]][ddata->map_pos[1]] == 1);
}

void		put_it(t_img screen, int i, int j, int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	char			*ptr;

	r = (unsigned char)(color >> 16);
	g = (unsigned char)((color % 65536) >> 8);
	b = (unsigned char)(color % 256);

	ptr = screen.data + j * screen.size_line + i * (screen.bpp >> 3);
	*ptr = screen.endian ? r : b;
	*(ptr + 1) = g;
	*(ptr + 2) = screen.endian ? b : r;
}

int			texture_to_color(t_img texture_img, double wall_x, double x)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	ptr = texture_img.data + (int)(x * texture_img.height) * texture_img.size_line
		+ (int)(wall_x * texture_img.width) * (texture_img.bpp >> 3);
	r = (unsigned char)(texture_img.endian ? *ptr : *(ptr + 2));
	g = (unsigned char)(*(ptr + 1));
	b = (unsigned char)(texture_img.endian ? *(ptr + 2) : *ptr);

	return ((r << 16) + (g << 8) + b);
}

void		draw_line(int x, t_game *game, t_text the_texture)
{
	int		j;
	int		color;
	t_img	texture_img;
	int		start;
	int		end;

	start = game->scr_h / 2 - the_texture.line_height / 2;
	end = game->scr_h / 2 + the_texture.line_height / 2;

	// start = start < 0 ? 0 : start;
	// end = end >= game->scr_h ? game->scr_h - 1 : end;
	texture_img = game->textures[the_texture.side];
	j = 0;
	while (j < (start < 0 ? 0 : start))
		put_it(game->screen, x, j++, game->color_ceil);
	while (j < (end >= game->scr_h ? game->scr_h - 1 : end))
	{
		color = texture_to_color(texture_img, the_texture.wall_x, ((j - start) * 1.0) / (end - start));
		put_it(game->screen, x, j++, color);
	}
	while (j < game->scr_h)
		put_it(game->screen, x, j++, game->color_floor);
}

void		dda(t_game *game, double ray[2], int i)
{
	t_bool		hit;
	t_dda		ddata;
	t_text		texture;

	hit = FALSE;
	ddata = init_dda(game, ray);
	while (!hit)
		hit = is_hit(game, &ddata, &texture, ray);
	texture.wall_dist = (texture.side == N || texture.side == S)
		? (ddata.map_pos[0] - game->pos[0] + (1 - ddata.step[0]) / 2) / ray[0]
		: (ddata.map_pos[1] - game->pos[1] + (1 - ddata.step[1]) / 2) / ray[1];
	game->depth_buffer[i] = texture.wall_dist;
	texture.wall_x = (texture.side == N || texture.side == S)
		? game->pos[1] + texture.wall_dist * ray[1]
		: game->pos[0] + texture.wall_dist * ray[0];
	texture.wall_x -= floor(texture.wall_x);
	texture.line_height = texture.wall_dist > 0 ? game->scr_h / texture.wall_dist : 2147483647;

	draw_line(i, game, texture);
}

void		wallz(t_game *game)
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
		dda(game, ray, i);
		i++;
	}
}

void		spr1tes(t_game *game)
{
	/**
	 * while raycasting walls, store perp distance of each
	 * vertical stripe
	 * calculate distancce from each sprite to player
	 * use distance to sort sprites
	 * project sprite on the cam plane (in 2D)
	 * => sub(player_pos, sprite_pos)
	 * => then multiply the result with
	 * inverse on the 2x2 cam matrix
	 * calculate size of sprite using perp distance
	 * draw sprite vertical stripe
	 * BUT dont draw verStripe if the distance is further
	 * away than 1D ZBuffer of the walls of curr_stripe
	 * draw vertical stripe pixel by pixel
	 * make sure there's an invisible color
	 * or all stripes will look like rectangles?
	 */
	
}

void		draw(t_game *game)
{
	wallz(game);
	spr1tes(game);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win,
		game->screen.ptr, 0, 0);
}
