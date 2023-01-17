#pragma once

#include "main.hpp"

class GraphicItem{
    private:
    SDL_Rect dst;
    int x, y;
    int *pos;

    public:
    SDL_Rect *org = nullptr;
    SDL_Texture *texture = nullptr;
    ID id;

    GraphicItem();
    GraphicItem(SDL_Texture *texture, int y, int x, ID id);
//    ~GraphicItem();

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