/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:45 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 15:48:46 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel_to_image(t_game *g, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = (y * g->size_line) + (x * (g->bpp / 8));
		g->img_data[pixel + 0] = color & 0xFF;
		g->img_data[pixel + 1] = (color >> 8) & 0xFF;
		g->img_data[pixel + 2] = (color >> 16) & 0xFF;
	}
}

void	clear_image(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_to_image(g, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_ceiling_and_floor(t_game *g, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
		put_pixel_to_image(g, x, y++, g->map_info->ceiling_clr);
	y = draw_end + 1;
	while (y < HEIGHT)
		put_pixel_to_image(g, x, y++, g->map_info->floor_clr);
}
