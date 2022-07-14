/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:54:37 by afaustin          #+#    #+#             */
/*   Updated: 2022/07/13 21:16:07 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_game(t_game *game);

void	error(char *msg, t_game *game)
{
	dprintf(2, "Error\n%s.\n%s\n", msg, strerror(errno));
	free_game(game);
	exit(errno);
}

void	end_program(t_game *game)
{
	free_game(game);
	exit(errno);
}

static void	free_game(t_game *game)
{
	if (game)
	{
		if (game->file_content != INPUT_ERR)
			ft_free_null(game->file_content);
		ft_free_matrix((void **)game->params.map, 0);
		ft_free_matrix((void **)game->params.textures, 4);
		ft_free_matrix((void **)game->params.rgb[0], 0);
		ft_free_matrix((void **)game->params.rgb[1], 0);
		ft_free_null(game);
	}
}