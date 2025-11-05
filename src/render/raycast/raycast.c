/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:39:15 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/03 18:02:24 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void    drawVerticalLine(t_game *game, int x, int d_start, int d_end, int color)
{
    while (d_start <= d_end)
    {
        draw_pixel_in_image(&game->screen, x, d_start, color);
        d_start++;
    }
}

void    raycast(t_game *game)
{
    int     collum = 0;
    double  deltaDistX;
    double  deltaDistY;
    double  sideDistX;
    double  sideDistY;
    int     stepX;
    int     stepY;
    double  perpWallDist;

    while (collum < SCREEN_WIDTH)
    {
        int     mapX = (int)game->player.pos.x;
        int     mapY = (int)game->player.pos.y;
        double cameraX = 2.0 * collum / (double)SCREEN_WIDTH - 1;
        double rayDirX = game->player.dir.x + game->player.plane.x * cameraX;
        double rayDirY = game->player.dir.y + game->player.plane.y * cameraX;
        
        deltaDistX = fabs(1 / rayDirX);
        deltaDistY = fabs(1 / rayDirY);

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.pos.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.pos.y) * deltaDistY;
        }
        int hit = 0;
        int side = 0;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // bateu numa parede vertical
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // bateu numa parede horizontal
            }
            if (mapX < 0 || mapY < 0 || mapX >= game->map_w || mapY >= game->map_h)
            {  
                hit = 1;
                break; // evita sair dos limites
            }
            
            // verifica se chegou em uma parede
            if (game->map[mapY * game->map_w + mapX] == '1')
            {
                hit = 1;
            }
        }
        //double wallx;

        if (side == 0)
            perpWallDist = sideDistX - deltaDistX;
        else
            perpWallDist = sideDistY - deltaDistY;
        double perpWallDistCorrected = perpWallDist * 
        (game->player.dir.x * rayDirX + game->player.dir.y * rayDirY);
        //wallx -= floor(wallx);*/
        
        int line_height = (int)(SCREEN_HEIGHT / perpWallDistCorrected);
        int drawStart = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = line_height / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;
        for (int i = 0; i < drawStart; i++)
            draw_pixel_in_image(&game->screen, collum, i, 0x9999FF);
        drawVerticalLine(game, collum, drawStart, drawEnd, 0x000000);
        for (int i = drawEnd; i < SCREEN_HEIGHT; i++)
            draw_pixel_in_image(&game->screen, collum, i, 0x888888);
        collum++;
    }
}