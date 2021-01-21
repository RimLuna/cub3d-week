/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:56:13 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/21 12:11:41 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			get_pixels_for_bmp(t_img screen, int i, int j)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	ptr = screen.data + j * screen.size_line + i * (screen.bpp >> 3);
	r = (unsigned char)(screen.endian ? *ptr : *(ptr + 2));
	g = (unsigned char)(*(ptr + 1));
	b = (unsigned char)(screen.endian ? *(ptr + 2) : *ptr);
	return ((r << 16) + (g << 8) + b);
}

void		reverse_for_bmp(t_game *game)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (i < game->scr_w)
	{
		j = 0;
		while (j < game->scr_h / 2)
		{
			tmp = get_pixels_for_bmp(game->screen, i, j);
			put_it(game->screen, i, j,
				get_pixels_for_bmp(game->screen, i, game->scr_h - j - 1));
			put_it(game->screen, i, game->scr_h - j - 1, tmp);
			j++;
		}
		i++;
	}
}

void		ugh_bmp(t_game *game)
{
	reverse_for_bmp(game);
	write(game->fd_save, game->screen.data, game->nb_pixels);
	close(game->fd_save);
}

void		put_bytes(char *dest, int nb, int nb_bytes)
{
	int		shift;
	int		i;

	i = nb_bytes - 1;
	shift = (nb_bytes > 1) ? (nb_bytes - 1) * 8 : 0;
	while (shift > 0)
	{
		dest[i] = (nb >> shift) & 0xFF;
		shift -= 8;
		i--;
	}
	dest[i] = nb & 0xFF;
}

void		bmp_header(t_game *game)
{
	char	header[54];

	header[0] = 'B';
	header[1] = 'M';
	put_bytes(&header[2], 54 + game->nb_pixels, 4);
	put_bytes(&header[6], 0, 4);
	put_bytes(&header[10], 54, 4);
	put_bytes(&header[14], 40, 4);
	put_bytes(&header[18], game->scr_w, 4);
	put_bytes(&header[22], game->scr_h, 4);
	put_bytes(&header[26], 1, 2);
	put_bytes(&header[28], game->screen.bpp, 2);
	put_bytes(&header[30], 0, 4);
	put_bytes(&header[34], game->nb_pixels, 4);
	put_bytes(&header[38], 0, 16);
	write(game->fd_save, header, 54);
}
