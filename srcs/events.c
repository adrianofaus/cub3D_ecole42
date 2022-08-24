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

int	key_press(int keycode, t_game *game)
{
	if (keycode == ARROW_RIGHT)
		game->player.move_direction = TURN_RIGHT;
	else if (keycode == ARROW_LEFT)
		game->player.move_direction = TURN_LEFT;
	else if (keycode == 'a')
		game->player.walk_direction = WALK_LEFT;
	else if (keycode == 'd')
		game->player.walk_direction = WALK_RIGHT;
	else if (keycode == 's')
		game->player.walk_direction = WALK_DOWN;
	else if (keycode == 'w')
		game->player.walk_direction = WALK_UP;
	else if (ft_strchr("1234", keycode))
		game->player.weapon = keycode - '0' - 1;
	else if (keycode == ESC)
		end_program(game);
	else if (keycode == CTRL)
		game->player.is_shooting = true;
	else if (keycode == 'e')
		return (open_door(game));
	else
		return (0);
	move_player(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == ARROW_RIGHT)
		game->player.move_direction = 0;
	else if (keycode == ARROW_LEFT)
		game->player.move_direction = 0;
	else if (keycode == 'd')
		game->player.walk_direction = 0;
	else if (keycode == 'a')
		game->player.walk_direction = 0;
	else if (keycode == 's')
		game->player.walk_direction = 0;
	else if (keycode == 'w')
		game->player.walk_direction = 0;
	else if (keycode == CTRL)
		game->player.is_shooting = false;
	return (0);
}

int	mouse_click(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	// printf("%d\n", game->player.is_shoting);
	if (button == LEFT_CLICK)
	{
		game->player.is_shooting = true;
		game->player.has_shooted = false;
	}
	else if (button == RIGHT_CLICK)
		open_door(game);
	else if (button == SCROLL_UP)
	{
		if (game->player.weapon)
			game->player.weapon--;
		else
			game->player.weapon = WEAPONS_TYPES - 1;
	}
	else if (button == SCROLL_DOWN)
	{
		if (game->player.weapon < WEAPONS_TYPES - 1)
			game->player.weapon++;
		else
			game->player.weapon = 0;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLICK && game->player.has_shooted)
	{
		game->player.is_shooting = false;
		game->player.has_shooted = false;
	}
	return (0);
}
