/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:52 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/19 12:48:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	toggle_door(t_door *door)
{
	if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENING;
	else if (door->state == DOOR_OPEN)
		door->state = DOOR_CLOSING;
}

void	update_door(t_door *door, double dt)
{
	double	progress;

	if (door->state == DOOR_OPENING)
	{
		door->anim_time += dt;
		if (door->anim_time >= door->anim_duration)
		{
			door->anim_time = door->anim_duration;
			door->state = DOOR_OPEN;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->anim_time -= dt;
		if (door->anim_time <= 0.0)
		{
			door->anim_time = 0.0;
			door->state = DOOR_CLOSED;
		}
	}
	progress = door->anim_time / door->anim_duration;
	door->current_frame = (int)(progress * door->frame_count);
	if (door->current_frame >= door->frame_count)
		door->current_frame = door->frame_count - 1;
}
