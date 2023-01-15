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

    //the wall
    for (int i = 0; i < width; i++){
        display->screen[0][i] = wall;
        display->screen[height - 1][i] = wall;
    }
    for (int i = 1; i < height - 1; i++){
        for (int j = 0; j < width; j++){
            if (j == 0 || j == width - 1){
                display->screen[i][j] = wall;
            }
            else{
                display->screen[i][j] = space;
            }
        }
    }

    //The start of the snake

}