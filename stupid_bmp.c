/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:03:31 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/19 17:53:21 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_bytes(char *dest, int nb, int nb_bytes)
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

void	bmp_header(t_game *game)
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
