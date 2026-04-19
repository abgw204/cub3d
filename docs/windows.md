# Windows (MSYS2 + MinGW-w64)

This builds the raylib client only (`cub3d_rl.exe`). The server stays on POSIX.

## Install MSYS2

1. Install MSYS2: https://www.msys2.org/
2. Open the **MSYS2 MinGW x64** shell.

## Dependencies

```bash
pacman -S --needed \
  mingw-w64-x86_64-toolchain \
  mingw-w64-x86_64-cmake \
  mingw-w64-x86_64-ninja
```

## Build

From the repo root:

```bash
cmake -S . -B build/cmake -G Ninja
cmake --build build/cmake
```

## Run

Run from the repo root (so `res/` is found):

```bash
./build/cmake/cub3d_rl.exe res/maps/aaa.cub 0 127.0.0.1 5000
```

## Zip Package

```bash
cmake --build build/cmake --target package_zip
```

It produces `build/cmake/cub3d_rl_Windows.zip`.
