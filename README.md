# A Multi-Player Snake game in SDL

## Screenshots

![menu](https://raw.githubusercontent.com/SL-Pirate/snake/main/screenshots/menu.png)
![game](https://raw.githubusercontent.com/SL-Pirate/snake/main/screenshots/game.png)
![multiplayer](https://raw.githubusercontent.com/SL-Pirate/snake/main/screenshots/multiplayer.png)
![paused](https://raw.githubusercontent.com/SL-Pirate/snake/main/screenshots/paused.png)
![game over](https://raw.githubusercontent.com/SL-Pirate/snake/main/screenshots/gameOver.png)

## Dependencies

Tools you need to install yourself:

- git
- CMake 3.24 or newer
- [Conan 2](https://conan.io/) (`pip install conan`)
- A C++ compiler (GCC or Clang on Linux, MSVC or MinGW on Windows)

Libraries are handled by Conan. You do not need to install them manually:

- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer
- wxWidgets

The exact versions are pinned in `conanfile.txt`.

## Building

The steps are the same on every platform.

```sh
git clone https://github.com/SL-Pirate/snake
cd snake
conan profile detect --force
conan install . --build=missing
cmake --preset conan-release
cmake --build --preset conan-release
```

Notes:

- `conan profile detect` only needs to run once per machine.
- The first `conan install` can take a while. Conan builds any library that has no prebuilt binary for your setup. Later builds reuse the Conan cache.
- The binary ends up in `build/Release/`.

### Windows with MSVC

Run the commands above from a *Developer Command Prompt for VS* so Conan can find the compiler.
MSVC uses a multi-config CMake generator, so the configure preset has a different name:

```sh
cmake --preset conan-default
cmake --build --preset conan-release
```

### Linux system packages

A few dependencies (xorg, opengl, egl, xkeyboard-config) come from your distro's package manager, not from Conan.
`conan install` checks for them and lists anything that is missing. Install those packages and run it again, or let Conan install them for you:

```sh
conan install . --build=missing --output-folder=build \
  -c tools.system.package_manager:mode=install \
  -c tools.system.package_manager:sudo=True

cmake .. -DCMAKE_TOOLCHAIN_FILE="Release/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="release"
cmake --build .
```

## Running

All resources (fonts, images, sounds) are compiled into the executable. The binary runs on its own and can be copied anywhere.

```sh
./build/Release/snake
```

On Windows run `build\Release\snake.exe`.
