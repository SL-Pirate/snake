# Snake game in sdl, my own version

## build dependancies

- wxWidgets
- SDL2
- SDL2_image
- SDL2_ttf
- cmake
- git

## Building in linux

```sh
git clone github.com/SL-Pirate/snake
cd snake
mkdir build
cd build
cmake ..
make
```
### To Run the program
do `sudo chmod +x ./snake`
- This needs to be done only once!
- after this is done just execute the `snake` binary from a command line or a graphical file manager.

## Building for windows
### Setting up building environment for windows

1. Download and install wxWidgets from their official website
1. Add the path_to_the_root_of_your_wxWidgets_folder to your system environment variables under the name `wxWidgets`
1. Download the development packages of 
    - SDL2
    - SDL2_image
    - SDL2_ttf
    
    corresponding to your compiler
1. Extract the development package of SDL2 and rename the directory as SDL2
1. Extract the development package of SDL2_image to the same folder and rename it as SDL2_image
1. Extract the development package of SDL2_image to the same folder and rename it as SDL2_ttf

    Now your directory should look like this
    ```tree
    {BaseFolder}
    ├── SDL2
        ├── cmake
        ├── include
        ├── lib
        etc...
    .......
        SDL2_image
        ├── cmake
        ├── include
        ├── lib
        etc...
    ........
        SDL2_ttf
        ├── cmake
        ├── include
        ├── lib
        etc...
    ```
### Compiling
- if using `MinGW32-gcc`
```sh
git clone github.com/SL-Pirate/snake
cd snake
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
make
```
- if using msvc
```sh
git clone github.com/SL-Pirate/snake
cd snake
mkdir build
cd build
cmake --build ..
```