#pragma once

#include "main.hpp"
#include "sdl_window.hpp"

enum Dir{up, down, left, right};

class Entity{
    protected:
    Window *gameWin = nullptr;
    SDL_Texture *texture = nullptr;
    //GraphicItem *arr[rows][cols];
    GraphicItem ***arr;
    
    public:
    Entity();
};


class Snake : public Entity {
    GraphicItem *snake[rows*cols];
    int length = 0;
    Dir dir = right;
    
    public:
    Snake(Window *gameWin, GraphicItem ***arr);
    void addToArr();
    void move();
    void move(Dir direction);
};


class Wall : public Entity {
    public:
    int c = 0;
    Wall(Window *gameWin, GraphicItem ***arr);
};


class GraphicItem{
    private:
    SDL_Rect dst;
    int x, y;

    public:
    SDL_Rect *org = nullptr;
    SDL_Texture *texture = nullptr;

    GraphicItem();
    GraphicItem(SDL_Texture *texture, int y, int x);
    ~GraphicItem();

    SDL_Rect *getDst();

    /**takes positions of x and y in "In Game Units*" 
    
    NOTE: 1 in game unit = size of the graphic item which is 16px in standard
    Therefore no if total in game units can be calculated by total screen width (in pixels)
    divided by size of the graphic item
    
    *and sets the position cordinates x, y values in pixels
    so they can be easily rendered
    */
    void setPos(int y, int x);

    /*returns a pointer of position in "In Game Units"
    in the form of int list[x] where x can either be 0 (for x cordinate) or 1 (for y cordinate)
    
    NOTE: 1 in game unit = size of the graphic item which is 16px in standard
    Therefore no if total in game units can be calculated by total screen width (in pixels)
    divided by size of the graphic item
    */
    int *getPos();
};