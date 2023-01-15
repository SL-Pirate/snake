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
    //implemented for testing assuming the body is all in a single direction
    //i.e. not bent from anywhere
    while (true){
        for (int i = 0; i < body->length; i++){
            switch(body->direction){
                case body->up:
                    body->snake[i][body->v]++;
                    break;
                case body->down:
                    body->snake[i][body->v]--;
                    break;
                case body->left:
                    body->snake[i][body->h]--;
                    break;
                case body->right:
                    body->snake[i][body->h]++;
            }
            body->addToDisplay();
            system("clear");
            body->display->draw();

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}