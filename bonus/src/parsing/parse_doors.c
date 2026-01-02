/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:26:06 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/02 15:45:02 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h" // free_all(NULL, get_data()->config, "")

static bool	door_in_bounds(t_iv2 door, int map_w, int map_h)
{
	return (door.x + 1 < map_w && door.x - 1 >= 0
		&& door.y + 1 < map_h && door.y - 1 >= 0);
}

static int	validate_door(char *map, t_iv2 door, int map_w, int map_h)
{
	if (!door_in_bounds(door, map_w, map_h))
		return (1);
	if (map[door.y * map_w + (door.x + 1)] == '1'
		&& map[door.y * map_w + (door.x - 1)] == '1'
		&& map[(door.y + 1) * map_w + door.x] == '0'
		&& map[(door.y - 1) * map_w + door.x] == '0')
		return (0);
	if (map[(door.y + 1) * map_w + door.x] == '1'
		&& map[(door.y - 1) * map_w + door.x] == '1'
		&& map[door.y * map_w + (door.x + 1)] == '0'
		&& map[door.y * map_w + (door.x - 1)] == '0')
		return (0);
	return (1);
}

static int	verify_doors(char *map, int map_w, int map_h)
{
	unsigned int	i;
	t_iv2			*doors;

	i = -1;
	doors = get_data()->doors;
	while (++i < get_data()->doors_n)
	{
		if (validate_door(map, doors[i], map_w, map_h))
		{
			free(map);
			return (free_all(NULL, get_data()->config, "Invalid door in map!"));
		}
	}
	return (0);
}

int	parse_doors(char *map, int map_w, int map_h)
{
	int		i;
	t_iv2	pos;

	i = -1;
	pos.x = i;
	pos.y = i;
	if (!get_data()->doors_n)
		return (0);
	get_data()->doors = (t_iv2 *)malloc(get_data()->doors_n * sizeof(t_iv2));
	if (!get_data()->doors)
		return (free_all(NULL, get_data()->config, "Memory allocation failed!"));
	while (++pos.y < map_h)
	{
		while (++pos.x < map_w)
			if (map[pos.y * map_w + pos.x] == 'D')
				get_data()->doors[++i] = pos;
		pos.x = -1;
	}
	if (verify_doors(map, map_w, map_h))
		return (1);
	return (0);
}