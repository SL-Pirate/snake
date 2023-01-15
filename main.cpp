#include "main.hpp"

int main(){
    Display *display = new Display();
    draw(display);
    display->draw();

    return 0;
}

void draw(Display *display){
    //clear the literal screen
    system("clear");

    //The start of the snake
    display->screen[9][29] = body;
    display->screen[9][30] = body;
}