/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:47:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/08/25 20:37:39 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_sprite_properties(t_game *game, int id);
static void	get_sprite_dimension(t_game *game, int id);

void	draw_3d_sprites(t_game *game)
{
	int		i;
	int		x;
	int		y;
	int		distance_from_top;
	int		texture_offset_y;
	int		texture_offset_x;
	float	texel_width;
	u_int32_t	color;

	i = 0;
	while (i < game->sprites_num)
	{
		if (game->sprites[i].is_visible)
		{
			get_sprite_dimension(game, i);
			get_sprite_properties(game, i);
			x = game->texture_prop->offset_x;
			int	var = x / 2 + (game->texture_prop->width / 2) - ((game->texture_prop->width - game->texture_prop->offset_x) * 0.15);
			int	var2 = x / 2 + (game->texture_prop->width / 2) + ((game->texture_prop->width - game->texture_prop->offset_x) * 0.15);
			for (int z = x; z < game->texture_prop->width; z++)
			{
				draw_pixel(game->img, z, game->window_height / 2, WHITE);
			}
			for (int z = 0; z < game->texture_prop->offset_y; z++)
			{
				draw_pixel(game->img, var, z, RED);
				draw_pixel(game->img, var2, z, RED);
			}
			while (x < game->texture_prop->width)
			{
				texel_width = game->sprites[i].img->width / game->wall_prop->proj_wall_height;
				texture_offset_x = (x - game->texture_prop->offset_x) * texel_width;
				y = game->texture_prop->offset_y;
				if (x > 0 && x < game->window_width && game->rays[x].coord.hipo > game->sprites[i].coord.hipo)
				{
					while (y < game->texture_prop->height)
					{
						if (y > 0 && y < game->window_height)
						{
							distance_from_top = y + (game->wall_prop->proj_wall_height / 2) - (game->window_height / 2);
							texture_offset_y = distance_from_top * (game->sprites[i].img->height / game->wall_prop->proj_wall_height);
							color = get_color(game->sprites[i].img, texture_offset_x, texture_offset_y);
							if (color != 0xB3008C)
								draw_pixel(game->img, x, y, color);
						}
						y++;
					}
				}
				x++;
			}
		}
		i++;
	}
}

static void	get_sprite_dimension(t_game *game, int id)
{
	game->wall_prop->proj_wall_dist = (game->window_width / 2) \
		/ tan(FOV_ANGLE / 2);
	game->wall_prop->proj_wall_height = \
		(TILE_SIZE / game->sprites[id].coord.hipo) * \
		game->wall_prop->proj_wall_dist;
}

static void	get_sprite_properties(t_game *game, int id)
{
	float	sprite_angle;
	
	sprite_angle = atan2(game->sprites[id].coord.y - game->player.coord.y, \
				game->sprites[id].coord.x - game->player.coord.x) - \
				game->player.coord.angle;
	game->texture_prop->offset_y = (game->window_height / 2) - \
		((int)game->wall_prop->proj_wall_height / 2);
	if (game->texture_prop->offset_y < 0)
		game->texture_prop->offset_y = 0;
	game->texture_prop->offset_x = (tan(sprite_angle) * \
		game->wall_prop->proj_wall_dist) + (game->window_width / 2) - (game->wall_prop->proj_wall_height / 2);
	game->texture_prop->width = game->texture_prop->offset_x + game->wall_prop->proj_wall_height;
	game->texture_prop->height = (game->window_height / 2) + \
		((int)game->wall_prop->proj_wall_height / 2);
	if (game->texture_prop->height > game->window_height)
		game->texture_prop->height = game->window_height;
}



void	get_visible_sprites(t_game *game)
{
	int		i;
	float	sprite_angle;

	i = 0;
	while (i < game->sprites_num)
	{
		sprite_angle = game->player.coord.angle - \
			atan2(game->sprites[i].coord.y - game->player.coord.y, \
				game->sprites[i].coord.x - game->player.coord.x);
		if (sprite_angle > M_PI)
			sprite_angle -= (M_PI + M_PI);
		if (sprite_angle < -M_PI)
			sprite_angle += (M_PI + M_PI);
		sprite_angle = fabs(sprite_angle);
		if (sprite_angle < (FOV_ANGLE / 2) + EPSILON)
		{
			game->sprites[i].is_visible = true;
			game->sprites[i].coord.angle = sprite_angle;
			game->sprites[i].coord.hipo = calculate_hipo(\
				game->player.coord.x - game->sprites[i].coord.x, \
				game->player.coord.y - game->sprites[i].coord.y\
			);
		}
		else
			game->sprites[i].is_visible = false;
		i++;
	}
}
