#include "cub3d.h"

void			init_camera(t_game *game)
{
	if (game->cam_dir == E || game->cam_dir == W)
	{
		game->dir[0] = 0;
		game->dir[1] = (game->cam_dir == E) ? 1 : -1;
		game->cam_plane[0] = (game->cam_dir == E) ? 0.66 : -0.66;
		game->cam_plane[1] = 0;
	}
	else
	{
		game->dir[0] = (game->cam_dir == S) ? 1 : -1;
		game->dir[1] = 0;
		game->cam_plane[0] = 0;
		game->cam_plane[1] = (game->cam_dir == S) ? -0.66 : 0.66;
	}
}

t_bool			init_screen(t_game *game)
{
	if (!(game->screen.ptr = mlx_new_image(game->mlx.ptr,
		game->scr_w, game->scr_h)))
		return (FALSE);
	if (!(game->screen.data = mlx_get_data_addr(game->screen.ptr,
		&(game->screen.bpp), &(game->screen.size_line),
		&(game->screen.endian))))
		return (FALSE);
	return (TRUE);
}