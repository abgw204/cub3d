/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:18:14 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/19 11:58:27 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	move_w(t_game *game, t_player *player)
{
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (player->dir.x > 0.0)
		coll_x = COLLISION_DIST;
	else
		coll_x = -COLLISION_DIST;
	if (player->dir.y > 0.0)
		coll_y = COLLISION_DIST;
	else
		coll_y = -COLLISION_DIST;
	new_x = player->pos.x + player->dir.x * player->speed * g_delta_time;
	new_y = player->pos.y + player->dir.y * player->speed * g_delta_time;
    if (game->map[(int)game->player.pos.y * game->map_w + (int)(new_x + coll_x)] != '1')
		player->pos.x = new_x;
	if (game->map[(int)(new_y + coll_y) * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

void	move_a(t_game *game, t_player *player)
{
	t_dv2	side;
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (-player->plane.x > 0.0)
		coll_x = COLLISION_DIST;
	else
		coll_x = -COLLISION_DIST;
	if (-player->plane.y > 0.0)
		coll_y = COLLISION_DIST;
	else
		coll_y = -COLLISION_DIST;
    side.x = player->dir.y;
	side.y = -player->dir.x;
    new_x = player->pos.x + side.x * player->speed * g_delta_time;
    new_y = player->pos.y + side.y * player->speed * g_delta_time;
	if (game->map[(int)game->player.pos.y * game->map_w + (int)(new_x + coll_x)] != '1')
		player->pos.x = new_x;
	if (game->map[(int)(new_y + coll_y) * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

void	move_s(t_game *game, t_player *player)
{
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (player->dir.x > 0.0)
		coll_x = -COLLISION_DIST;
	else
		coll_x = COLLISION_DIST;
	if (player->dir.y > 0.0)
		coll_y = -COLLISION_DIST;
	else
		coll_y = COLLISION_DIST;
	new_x = player->pos.x + -player->dir.x * player->speed * g_delta_time;
	new_y = player->pos.y + -player->dir.y * player->speed * g_delta_time;
    if (game->map[(int)game->player.pos.y * game->map_w + (int)(new_x + coll_x)] != '1')
		player->pos.x = new_x;
	if (game->map[(int)(new_y + coll_y) * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

void	move_d(t_game *game, t_player *player)
{
    t_dv2	side;
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (player->plane.x > 0.0)
		coll_x = COLLISION_DIST;
	else
		coll_x = -COLLISION_DIST;
	if (player->plane.y > 0.0)
		coll_y = COLLISION_DIST;
	else
		coll_y = -COLLISION_DIST;
    side.x = -player->dir.y;
	side.y = player->dir.x;
    new_x = player->pos.x + side.x * player->speed * g_delta_time;
    new_y = player->pos.y + side.y * player->speed * g_delta_time;
	if (game->map[(int)game->player.pos.y * game->map_w + (int)(new_x + coll_x)] != '1')
		player->pos.x = new_x;
	if (game->map[(int)(new_y + coll_y) * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

int	update_all_players(t_game *game, char *buffer, int latest_bytes)
{
	int	offset;
	int	id;
	int	i;

	i = -1;
	offset = 0;
    while (++i < MAX_PLAYERS)
    {
        if (offset + 28 > latest_bytes)
            break;
        memcpy(&id, buffer + offset, sizeof(int));
        if (id == game->my_id)
        {
            memcpy(&game->player.pos.x, buffer + offset + 4, sizeof(double));
            memcpy(&game->player.pos.y, buffer + offset + 12, sizeof(double));
			memcpy(&game->health, buffer + offset + 24, sizeof(int));
			printf("health: %d\n", game->health);
			if (game->health <= 0)
			{
				game->state = MAIN_MENU;
				return (1);
			}
        }
		else
		{
			memcpy(&game->players[i].id, buffer + offset, sizeof(int));
            memcpy(&game->players[i].x, buffer + offset + 4, sizeof(double));
            memcpy(&game->players[i].y, buffer + offset + 12, sizeof(double));
			memcpy(&game->players[i].connected, buffer + offset + 20, sizeof(int));
		}
        offset += SEND_PACKET_SIZE;
    }
	return (0);
}

int receive_position(t_game *game)
{
    char	tmp_buffer[MAX_PLAYERS * SEND_PACKET_SIZE];
    char	latest_buffer[MAX_PLAYERS * SEND_PACKET_SIZE];
    int		bytes;
    int		latest_bytes;

	game->soc.peer_len = sizeof(game->soc.peer);
	bytes = 1;
	latest_bytes = 0;
    while (bytes > 0)
	{
		bytes = recvfrom(game->soc.socket, tmp_buffer, sizeof(tmp_buffer), 0,
			(struct sockaddr *)&game->soc.peer, &game->soc.peer_len);
		if (bytes > 0 && bytes <= (int)sizeof(tmp_buffer))
		{
			memcpy(latest_buffer, tmp_buffer, bytes);
			latest_bytes = bytes;
		}
	}
	if (latest_bytes <= 0)
		return 0;
	return (update_all_players(game, latest_buffer, latest_bytes));
}

void	move_player(t_game *game)
{
    //t_player	*player;

    //player = &game->player;
	//printf("SENDTO\n");
	rotate_camera(game);
	mouse_move_in_game(game, game->m_x);
	memcpy(game->keys + 8, &game->player.angle, 8);
	if (sendto(game->soc.socket, game->keys, 17,
		0, (struct sockaddr*)&game->soc.peer, sizeof(game->soc.peer)) == -1)
		exit(EXIT_FAILURE);
}
