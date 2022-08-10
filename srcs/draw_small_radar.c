/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_radar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:51:21 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/09 22:26:07 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	copy_block(t_game *game, int i, int j);
static void	get_offset(t_game *game);

void	draw_small_radar(t_game *game)
{
	int	x;
	int	y;
	int	limit_x;
	int	limit_y;

	get_offset(game);
	limit_x = game->minimap.width;
	limit_y = game->minimap.height;
	if (game->minimap.width > 20)
		limit_x = 20;
	if (game->minimap.height > 11)
		limit_y = 11;
	game->texture_prop->height = 16;
	game->texture_prop->width = 16;
	y = 0;
	while (y < limit_y)
	{
		x = 0;
		while (x < limit_x)
		{
			copy_block(game, x, y);
			x++;
		}
		y++;
	}
}

static void	get_offset(t_game *game)
{
	int	player_line;
	int	player_column;

	player_line = (int)floor(game->player.coord.y / TILE_SIZE);
	player_column = (int)floor(game->player.coord.x / TILE_SIZE);
	if (player_line <= 5)
		game->texture_prop->offset_y = 0;
	else if (player_line >= game->minimap.height - 5)
		game->texture_prop->offset_y = (game->minimap.height - 11) * \
			game->minimap.tile_size;
	else
		game->texture_prop->offset_y = floor(game->player.coord.y * \
			MINIMAP_SCALE_FACTOR) - 90;
	if (player_column <= 10)
		game->texture_prop->offset_x = 0;
	else if (player_column >= game->minimap.width - 10)
		game->texture_prop->offset_x = (game->minimap.width - 20) * \
			game->minimap.tile_size;
	else
		game->texture_prop->offset_x = floor(game->player.coord.x * \
			MINIMAP_SCALE_FACTOR) - 160;
}

static void	copy_block(t_game *game, int j, int i)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->texture_prop->height)
	{
		x = 0;
		while (x < game->texture_prop->width)
		{
			draw_pixel(game->minimap.radars[BIG], \
				x + (j * game->minimap.tile_size), \
				y + (i * game->minimap.tile_size), \
				get_color(\
					game->minimap.radars[NORMAL], \
					game->texture_prop->offset_x + x + \
						(j * game->minimap.tile_size),
					game->texture_prop->offset_y + y + \
						(i * game->minimap.tile_size))
				);
			x++;
		}
		y++;
	}
}