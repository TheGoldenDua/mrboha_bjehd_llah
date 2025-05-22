/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_bang.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:37 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 16:51:59 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	big_bang(t_game g)
{
	g.mlx = mlx_init();
	if (!g.mlx)
		return (cleanup(&g), 1);
	if (!load_textures(&g))
		return (cleanup(&g), print_error("Failed to load textures", g.map_info),
			1);
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, "Raycaster JiBooR");
	g.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
	g.img_data = mlx_get_data_addr(g.img, &g.bpp, &g.size_line, &g.endian);
	if (!g.win || !g.img || !g.img_data)
	{
		cleanup(&g);
		return (1);
	}
	set_fov(&g, g.map_info->player_dir);
	if (convert_char_map_to_int(&g) == 1)
		return (cleanup(&g), 1);
	find_player_pos(&g);
	render_frame(&g);
	mlx_key_hook(g.win, handle_key, &g);
	mlx_hook(g.win, 17, 0, handle_exit, &g);
	mlx_loop(g.mlx);
	cleanup(&g);
	return (0);
}
