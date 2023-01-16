#include "main.hpp"

void Display::drawWall(){
    for (int i = 0; i < width; i++){
        screen[0][i] = wall;
        screen[height - 1][i] = wall;
    }
    for (int i = 1; i < height - 1; i++){
        for (int j = 0; j < width; j++){
            if (j == 0 || j == width - 1){
                screen[i][j] = wall;
            }
            else{
                screen[i][j] = space;
            }
        }
    }
}

void Display::draw(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << screen[i][j];
        }
        std::cout << std::endl;
    }
}

Body::Body(Display *display){
    direction = right;
    this->display = display;

    snake[0][0] = 9; snake[0][1] = 29;
    snake[1][0] = 9; snake[1][1] = 30;

    addToDisplay();
}

void Body::moveSnake(){
    for (int i = length - 1; i >= 1; i--){
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }
    switch (direction){
        case up:
            snake[0][v]++;
            break;
        case down:
            snake[0][v]--;
            break;
        case left:
            snake[0][h]--;
            break;
        case right:
            snake[0][h]++;
    }

    addToDisplay();
}

void Body::addToDisplay(){
    for (int i = 0; i < length; i++){
        display->screen[snake[i][0]][snake[i][1]] = body;
    }
}