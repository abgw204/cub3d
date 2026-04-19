/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_assets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

static Texture2D	load_wall_texture(const char *path)
{
	// We no longer support .xpm in configs.
	return (LoadTexture(path));
}

static int	find_config_idx(t_data *data, const char *key)
{
	for (int i = 0; data->config[i]; i++)
	{
		if (!ft_strcmp(data->config[i][0], (char *)key))
			return (i);
	}
	return (-1);
}

int	rl_assets_load(t_rl_assets *a, t_data *data)
{
	int	idx_no;
	int	idx_so;
	int	idx_we;
	int	idx_ea;

	memset(a, 0, sizeof(*a));
	idx_no = find_config_idx(data, "NO");
	idx_so = find_config_idx(data, "SO");
	idx_we = find_config_idx(data, "WE");
	idx_ea = find_config_idx(data, "EA");
	if (idx_no < 0 || idx_so < 0 || idx_we < 0 || idx_ea < 0)
		return (print_error("Invalid config: missing one or more texture paths"));
	a->walls.no = load_wall_texture(data->config[idx_no][1]);
	a->walls.so = load_wall_texture(data->config[idx_so][1]);
	a->walls.we = load_wall_texture(data->config[idx_we][1]);
	a->walls.ea = load_wall_texture(data->config[idx_ea][1]);
	if (a->walls.no.id == 0 || a->walls.so.id == 0 || a->walls.we.id == 0 || a->walls.ea.id == 0)
		return (print_error("Failed to load one or more wall textures via raylib"));
	a->enemy = LoadTexture("res/textures_png/sprites/enemy.png");
	a->gun_sheet = LoadTexture("res/textures_png/sprites/gun_spritesheet.png");

	// Audio is optional.
	a->audio_ok = false;
	a->gunshot = (Sound){0};
	InitAudioDevice();
	if (IsAudioDeviceReady())
	{
		a->audio_ok = true;
		a->gunshot = LoadSound("res/sounds/gunshot.mp3");
		if (a->gunshot.frameCount == 0)
			a->audio_ok = false;
		else
			SetSoundVolume(a->gunshot, 0.6f);
	}
	return (0);
}

void	rl_assets_unload(t_rl_assets *a)
{
	if (a->walls.no.id != 0)
		UnloadTexture(a->walls.no);
	if (a->walls.so.id != 0)
		UnloadTexture(a->walls.so);
	if (a->walls.we.id != 0)
		UnloadTexture(a->walls.we);
	if (a->walls.ea.id != 0)
		UnloadTexture(a->walls.ea);
	if (a->enemy.id != 0)
		UnloadTexture(a->enemy);
	if (a->gun_sheet.id != 0)
		UnloadTexture(a->gun_sheet);
	if (a->audio_ok)
		UnloadSound(a->gunshot);
	if (IsAudioDeviceReady())
		CloseAudioDevice();
}
