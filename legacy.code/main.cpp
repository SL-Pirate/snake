#include "main.hpp"

int main(){
//    initscr();
    Display *display = new Display();
    draw(display);
    Body *body = new Body(display);
    display->draw();
    std::thread loop(mainloop, body);
    std::thread kbLoop(keyboardInput, body);
//    loop.join();
    kbLoop.join();

    endwin();

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

void keyboardInput(Body *body){
    #ifdef __linux__
    initscr();
    while(true){
        int ch = getch();
//        std::cout << ch << std::endl;
        if (ch != ERR){
            switch (ch){
                case KEY_UP:
                    body->direction = Body::up;
                    break;
                case KEY_DOWN:
                    body->direction = Body::down;
                    break;
                case KEY_LEFT:
                    body->direction = Body::left;
                    break;
                case KEY_RIGHT:
                    body->direction = Body::right;
            }
        }
    }
    #endif
}