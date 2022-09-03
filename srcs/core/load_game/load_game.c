/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:24:00 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:24:00 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_radar_limits(t_game *game);

void	load_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error("Mlx init failed", game);
	load_window(game);
	load_images(game);
	load_textures(game);
	load_player(game);
	load_rays(game);
	load_menus(game);
	save_sprites(game);
}

void	load_window(t_game *game)
{
	game->window = mlx_new_window(game->mlx, game->window_width, \
		game->window_height, "cub3D");
	if (!game->window)
		error("Could not open a window", game);
}

void	load_images(t_game *game)
{
	game->minimap.widthpx = game->minimap.width * TILE_SIZE;
	game->minimap.heightpx = game->minimap.height * TILE_SIZE;
	game->img = mlx_new_image(game->mlx, game->window_width, \
		game->window_height);
	game->minimap.radars[NORMAL] = mlx_new_image(game->mlx, \
		game->minimap.width * MINIMAP_TILE_SIZE, \
		game->minimap.height * MINIMAP_TILE_SIZE \
	);
	game->minimap.minimap_size = NORMAL;
	if ((game->minimap.width * MINIMAP_TILE_SIZE) > \
			game->window_width * MINIMAP_SCALE_FACTOR || \
		(game->minimap.height * MINIMAP_TILE_SIZE) > \
			game->window_height * MINIMAP_SCALE_FACTOR)
	{
		game->minimap.radars[SMALL] = mlx_new_image(game->mlx, \
			game->window_width * MINIMAP_SCALE_FACTOR, \
			game->window_height * MINIMAP_SCALE_FACTOR \
		);
		game->minimap.minimap_size = SMALL;
		if (!game->minimap.radars[SMALL])
			error("Could not create images", game);
		set_radar_limits(game);
	}
	if (!game->img || !game->minimap.radars[NORMAL])
		error("Could not create images", game);
}

static void	set_radar_limits(t_game *game)
{
	game->minimap.small_radar_heightpx = \
	game->window_height * MINIMAP_SCALE_FACTOR;
	game->minimap.small_radar_widthpx = \
	game->window_width * MINIMAP_SCALE_FACTOR;
	if (game->minimap.width > game->window_width * \
		MINIMAP_SCALE_FACTOR / MINIMAP_TILE_SIZE)
	{
		game->minimap.small_radar_limit_x = \
			floor(game->minimap.small_radar_widthpx \
			/ (float)MINIMAP_TILE_SIZE);
	}
	else
		game->minimap.small_radar_limit_x = game->minimap.width;
	if (game->minimap.height > game->window_height * \
		MINIMAP_SCALE_FACTOR / MINIMAP_TILE_SIZE)
	{
		game->minimap.small_radar_limit_y = \
			floor(game->minimap.small_radar_heightpx \
			/ (float)MINIMAP_TILE_SIZE);
	}
	else
		game->minimap.small_radar_limit_y = game->minimap.height;
}
