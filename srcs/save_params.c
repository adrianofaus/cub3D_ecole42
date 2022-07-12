/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:02:02 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/07/05 21:44:49 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_env_colors(char *file_content, int identifier, t_game *game);
static int	get_textures(char *file_content, int identifier, t_game *game);
static int	get_map(char *file_content, t_game *game);
static int	is_textures(char *file_content, int *identifier);
static int	is_color(char *file_content, int *identifier);

void	save_params(t_game *game)
{
	int		i;
	int		identifier;
	int		elements;

	i = 0;
	elements = 0;
	while (game->file_content[i])
	{
		while (game->file_content[i] == '\n' && game->file_content[i])
			i++;
		if (is_textures(game->file_content + i, &identifier))
			i += get_textures(game->file_content + i, identifier, game);
		else if (is_color(game->file_content + i, &identifier))
			i += get_env_colors(game->file_content + i, identifier, game);
		else if (!game->params.map && elements == 6)
		{
			game->map_cub = game->file_content + i;
			i += get_map(game->file_content + i, game);
		}
		else if (game->file_content[i])
			error ("File configuration is invalid", game);
		if (!game->params.map)
			elements++;
	}
}

static int	is_color(char *file_content, int *identifier)
{
	if (!ft_strncmp(file_content, "F", 1))
		*identifier = ground;
	else if (!ft_strncmp(file_content, "C", 1))
		*identifier = celling;
	else
		return (0);
	return (1);
}

static int	is_textures(char *file_content, int *identifier)
{
	if (!ft_strncmp(file_content, "NO", 2))
		*identifier = NO;
	else if (!ft_strncmp(file_content, "SO", 2))
		*identifier = SO;
	else if (!ft_strncmp(file_content, "WE", 2))
		*identifier = WE;
	else if (!ft_strncmp(file_content, "EA", 2))
		*identifier = EA;
	else
		return (0);
	return (1);
}


static int	get_textures(char *file_content, int identifier, t_game *game)
{
	int		i;
	int		n;

	i = 2;
	while (ft_isspace(file_content[i]) && file_content[i] && \
			file_content[i] != '\n')
		i++;
	if ((i - 2) == 0)
		error("Invalid Identifier", game);
	n = 0;
	if (game->params.textures[identifier])
		error("Double Identifier", game);
	while (file_content[n] != '\n' && file_content[n])
		n++;
	game->params.textures[identifier] = ft_substr(file_content + 2, 0, n);
	if (!game->params.textures[identifier])
		error("Malloc Failed", game);
	return (n);
}

static int	get_env_colors(char *file_content, int identifier, t_game *game)
{
	int		i;
	int		n;
	char	*colors;

	i = 1;
	while (ft_isspace(file_content[i]) && file_content[i] && \
			file_content[i] != '\n')
		i++;
	if ((i - 1) == 0)
		error("Invalid Identifier", game);
	n = 0;
	if (game->params.rgb[identifier])
		error("Double Identifier", game);
	while (file_content[n] != '\n' && file_content[n])
		n++;
	colors = ft_substr(file_content + 1, 0, n);
	if (!colors)
		error("Malloc Failed", game);
	game->params.rgb[identifier] = ft_split(colors, ',');
	ft_free_null(colors);
	if (!game->params.rgb[identifier])
		error("Malloc Failed", game);
	return (n);
}

static int	get_map(char *file_content, t_game *game)
{
	int		lines;
	int		characters;

	game->params.map = ft_split(file_content, '\n');
	if (!game->params.map)
		error("Malloc Failed", game);
	lines = 0;
	characters = 0;
	while (game->params.map[lines])
		characters += ft_strlen(game->params.map[lines++]);
	return (characters + lines);
}