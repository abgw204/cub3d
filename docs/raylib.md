# raylib Integration (Linux)

This repo is migrating the renderer from MiniLibX to raylib.

## Dependencies (desktop Linux)

On Linux, raylib's desktop backend uses GLFW.

- On most distros this is effectively an X11 build (even on Wayland desktops it typically runs via XWayland).
- Because of that, building raylib from source usually requires X11 development headers.

To build raylib from the `third_party/raylib` submodule you need the usual X11 development packages:

- `libx11-dev`
- `libxext-dev`
- `libxrandr-dev`
- `libxcursor-dev`
- `libxinerama-dev`
- `libxi-dev`
- `libgl1-mesa-dev` (OpenGL)
- `libasound2-dev` (audio; optional for our minimal bootstrap but raylib enables it by default)

Package names vary by distro:

- Debian/Ubuntu: the `*-dev` names above.
- Fedora/RHEL: `libX11-devel libXext-devel libXrandr-devel libXcursor-devel libXinerama-devel libXi-devel mesa-libGL-devel alsa-lib-devel`.

## Build

1. Init/update submodules:

```bash
git submodule update --init --recursive
```

2. Build raylib:

- If you have raylib installed system-wide with `pkg-config`, `make rl` will use it automatically.
- Otherwise it will build raylib from `third_party/raylib` (static).

```bash
make raylib
```

3. Build the migration bootstrap binary:

```bash
make rl
```

4. Run:

```bash
./cub3d_rl
```

## Notes

- `cub3d_rl` is a minimal raylib app used to validate build/link during the migration.
- It compiles without MiniLibX by defining `CUB3D_NO_MLX`.
