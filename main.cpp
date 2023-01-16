#include "main.hpp"

int main(){
    Display *display = new Display();
    draw(display);
    Body *body = new Body(display);
    display->draw();
    std::thread loop(mainloop, body);
    loop.join();

    return 0;
}

void draw(Display *display){
    //clear the literal screen
    system("clear");
}

void mainloop(Body *body){
    //TODO - Implement keyboard input
    while (true){
        body->display->drawWall();
        body->moveSnake();

        system("clear");

        body->display->draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}