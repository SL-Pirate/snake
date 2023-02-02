#include "wxwids.hpp"
#include "game.hpp"
#include "snake.hpp"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(1010, cMain::start)
    EVT_BUTTON(1011, cMain::startMultiplayer)
    EVT_BUTTON(1012, cMain::resume)
    EVT_CLOSE(cMain::onClose)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Snake " VERSION, wxPoint(250, 50), wxSize(400, 400)){
#ifdef _WIN32
    this->SetBackgroundColour(*wxWHITE);
#endif
    this->Center();
    in = new wxStaticText(this, wxID_ANY, "welcome to the Snake Game\nPlease set difficulty:", wxPoint(50, 30), wxSize(300, 100), wxALIGN_CENTER);
    difficulty = new wxSlider(this, 1009, 10, 1, 20, wxPoint(50, 100), wxSize(300, 50));
    btn = new wxButton(this, 1010, "Start Singleplayer", wxPoint(33, 170), wxSize(150, 50));
    btn2 = new wxButton(this, 1011, "Start Multiplayer\n(Chaotic Mode)", wxPoint(217, 170), wxSize(150, 70));
    btn1 = new wxButton(this, 1012, "Resume", wxPoint(150, 220), wxSize(100, 50));
    btn1->Hide();
    out = new wxStaticText(this, wxID_ANY, outLabel, wxPoint(50, 290), wxSize(300, 140), wxALIGN_CENTER);
    out->Hide();
}
cMain::~cMain(){
    delete(difficulty);
    delete(game);
    delete(btn);
    delete(btn1);
    delete(out);
    delete(in);
    delete(t);
}
void cMain::start(wxCommandEvent &evt){
    this->Hide();
    btn->Hide();
    btn2->Hide();
    btn1->Show();
    game = new Game(this);
    t = new std::thread(startGame);
    out->Show();
}
void cMain::startMultiplayer(wxCommandEvent &evt){
    multiplayer = true;
    winWidth = 592;
    winHeight = 592;
    start(evt);
}
void cMain::resume(wxCommandEvent &evt){
    this->Hide();
    game->resume();
}
void cMain::onClose(wxCloseEvent &evt){
    exit(EXIT_SUCCESS);
}
void cMain::pause(){
    this->Show();
    if(!multiplayer){
        outLabel = "Your Score: ";
        outLabel << game->snake->getScore();
    }
    else{
        outLabel = "RED's Score: ";
        outLabel << game->snake1->getScore();
        outLabel << "\nBLUE's Score: ";
        outLabel << game->snake2->getScore();
    }
    out->SetLabel(outLabel);
}
void cMain::startGame(){
    if(multiplayer){
        game->startMultiplayer();
    }
    else{
        game->start();
    }
}
void cMain::quit(){
    if(!multiplayer){
        outLabel = "Game Over\nYour Score: ";
        outLabel << game->snake->getScore();
        btn->SetLabel("Restart Singleplayer");
    }
    else{
        winWidth = 496;
        winHeight = 496;
        outLabel = "Game Over\nRED's Score: ";
        outLabel << game->snake1->getScore();
        outLabel << "\nBLUE's Score: ";
        outLabel << game->snake2->getScore();
        btn2->SetLabel("Restart Multiplayer\n(Chaotic Mode)");
    }
    out->SetLabel(outLabel);
    btn1->Hide();
    btn->Show();
    btn2->Show();
    this->Show();
    game = nullptr;
    t = nullptr;
    multiplayer = false;

    SDL_Quit();
}
Game *cMain::game = nullptr;
bool cMain::multiplayer = false;


//Starting point of the program
bool cApp::OnInit(){
    main = new cMain();
    main->Show();

    return true;
}


wxIMPLEMENT_APP_NO_MAIN(cApp);

int main(int argc, char** argv){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        // std::cout << "Error: SDL INIT VIDEO FAILED!" << SDL_GetError() << std::endl;
    }

    return wxEntry(argc, argv);
}
// #endif