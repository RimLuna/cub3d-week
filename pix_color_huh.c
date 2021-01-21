/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_color_huh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:06:14 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/21 12:06:33 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	ptr = texture_img.data + (int)(x * texture_img.height)
		* texture_img.size_line
		+ (int)(wall_x * texture_img.width) * (texture_img.bpp >> 3);
	r = (unsigned char)(texture_img.endian ? *ptr : *(ptr + 2));
	g = (unsigned char)(*(ptr + 1));
	b = (unsigned char)(texture_img.endian ? *(ptr + 2) : *ptr);
	return ((r << 16) + (g << 8) + b);
}
