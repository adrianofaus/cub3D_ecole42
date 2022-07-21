/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 22:18:14 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/19 22:18:14 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_player(t_game *game);
static int	has_wall_at(t_game *game, int x, int y);

int	key_press(int keycode, t_game *game)
{
	if (keycode == 'd')
		game->player.move_direction = RIGHT;
	else if (keycode == 'a')
		game->player.move_direction = LEFT;
	else if (keycode == 's')
		game->player.walk_direction = DOWN;
	else if (keycode == 'w')
		game->player.walk_direction = UP;
	else if (keycode == ESC)
	{
		printf("Esc Pressed\n");
		end_program(game);//Refatorar f(x) para receber mensagem
	}
	else
		return (0);
	move_player(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 'd')
		game->player.move_direction = 0;
	else if (keycode == 'a')
		game->player.move_direction = 0;
	else if (keycode == 's')
		game->player.walk_direction = 0;
	else if (keycode == 'w')
		game->player.walk_direction = 0;
	return (0);
}

static void	move_player(t_game *game)
{
	int	move_step;
	int	to_x;
	int	to_y;

	game->player.coords.angle += game->player.move_direction * \
		game->player.rotation_speed;
	printf("Angle>: %f\n", game->player.coords.angle);
	move_step = game->player.walk_direction * MOVEMENT_SPEED;
	to_x = game->player.coords.x + cos(game->player.coords.angle) * move_step;
	to_y = game->player.coords.y + sin(game->player.coords.angle) * move_step;
	if (!has_wall_at(game, to_x, to_y))
	{
		game->player.coords.x = to_x;
		game->player.coords.y = to_y;
	}
}

static int	has_wall_at(t_game *game, int x, int y)
{
	if (x < 0 || x > game->width * TILE_SIZE || y < 0 || \
		y > game->height * TILE_SIZE)
		return (1);
	return (game->params.map[y / TILE_SIZE][x / TILE_SIZE] == '1');
}
