/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:35:36 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/19 16:35:38 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			free_map(t_game *game)
{
	int		i;

	if (game->map)
	{
		i = -1;
		while (++i < game->map_h)
			free(game->map[i]);
		free(game->map);
	}
}

void			free_game(t_game *game)
{
	t_side		side;

	side = N;
	if (game->z_buffer)
		free(game->z_buffer);
	if (game->sprites)
		free(game->sprites);
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
