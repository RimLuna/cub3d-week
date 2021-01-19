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

void		bmp_header(t_game *game)
{
	char		header[54];

	header[0] = 'B';
	header[1] = 'M';
	header[2] = get_bytes(54 + world->nb_pixels, 4);
	number_to_mem(&header[6], 0, 4);
	number_to_mem(&header[10], 54, 4);
	number_to_mem(&header[14], 40, 4);
	number_to_mem(&header[18], world->scr_width, 4);
	number_to_mem(&header[22], world->scr_height, 4);
	number_to_mem(&header[26], 1, 2);
	number_to_mem(&header[28], world->screen.bpp, 2);
	number_to_mem(&header[30], 0, 4);
	number_to_mem(&header[34], world->nb_pixels, 4);
	number_to_mem(&header[38], 0, 16);
	write(world->fd_save, header, 54);
}
