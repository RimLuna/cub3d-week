#include "cub3d.h"

t_bool		load_texture(t_game *game, t_img *texture, char *filename)
{
	if (!(texture->ptr = mlx_xpm_file_to_image(game->mlx.ptr,
		filename, &texture->width, &texture->height)))
		return (FALSE);
	if (!(texture->data = mlx_get_data_addr(texture->ptr, &texture->bpp,
		&texture->size_line, &texture->endian)))
		return (FALSE);
	return (TRUE);
}

void		init_textures(t_game *game)
{
	t_side	side;

	side = N;
	while (side <= E)
	{
		load_texture(game, &(game->textures[side]),
			game->textures[side].filename);
		side++;
	}
}

t_bool		finish_init(t_game *game)
{
	if (!parse_map2(game))
		return (FALSE);
	init_camera(game);
	if (!(game->mlx.ptr = mlx_init()))
		return (FALSE);
	init_textures(game);
	if (!(game->depth_buffer = ft_calloc(game->scr_w, sizeof(double))))
		return (FALSE);
	if (!init_screen(game))
		return (FALSE);
	game->nb_pixels = game->scr_w * game->scr_h * (game->screen.bpp >> 3);
	if (game->save)
	{
		game->fd_save = open("cub3d.bmp", O_RDONLY | O_CREAT, 0777);
	}
	else if (!(game->mlx.win = mlx_new_window(game->mlx.ptr, game->scr_w,
			game->scr_h, "cub3D")))
		return (FALSE);
	return (TRUE);
}

t_game		*game_init(int ac, char **av)
{
	t_game		*game;

	if (!(game = (t_game *)ft_calloc(1, sizeof(t_game))))
		return (NULL);
	if (ac < 2)
		parserror(game, "where the f is the file\n");
	else 
		if (ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".cub") != 0)
			parserror(game, "ext invalid!!\n");
	if ((game->fd = open(av[1], O_RDONLY)) < 0 ||
				(open(av[1], O_DIRECTORY) != -1))
		parserror(game, "no file or is it a dir??\n");
	parse_file(game);
	if (game->error)
	{
		free(game->raw_map);
		quit(game, ERROR);
	}
	game->save = (ac > 2) && (!ft_strcmp(av[2], "--save"));
	if (!finish_init(game))
		return (NULL);
	return (game);
}
