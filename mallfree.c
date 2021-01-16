#include "cub3d.h"

void			*ft_calloc(int count, int size)
{
	unsigned char	*ptr;
	int				i;

	if (!(ptr = malloc(count * size)))
		return (NULL);
	i = 0;
	while (i < count * size)
		*(ptr + i++) = 0;
	return ((void *)ptr);
}

void			free_game(t_game *game)
{
	t_side		side;
	int			i;

	side = N;
	if (game->depth_buffer)
		free(game->depth_buffer);
	if (game->sprites)
		free(game->sprites);
	if (game->map)
	{
		i = -1;
		while (++i < game->map_h)
			free(game->map[i]);
		free(game->map);
	}
	while (side <= E)
	{
		if (game->textures[side].filename)
			free(game->textures[side].filename);
		if (game->textures[side].data)
			mlx_destroy_image(game->mlx.ptr, game->textures[side].ptr);
		side++;
	}
	if (game->screen.data)
		mlx_destroy_image(game->mlx.ptr, game->screen.ptr);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.ptr, game->mlx.win);
	if (game->mlx.ptr)
		free(game->mlx.ptr);
	if (game->sprite_txt.filename)
		free(game->sprite_txt.filename);
	free(game);
}
