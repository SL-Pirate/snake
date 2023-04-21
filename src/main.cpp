#include "wxwids.hpp"
#include "game.hpp"
#include "entity.hpp"
#include "error.hpp"

int main(int argc, char** argv){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        throw SDL_InitError();
        return 101;
    }

    return wxEntry(argc, argv);
}

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
    in = new wxStaticText(this, wxID_ANY, "welcome to the Snake Game\nPlease set difficulty:", wxPoint(50, 30), wxSize(300, 50), wxALIGN_CENTER);
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
    try{
        game = new Game(this);
        t = new std::thread(startGame);
        out->Show();
    }
    catch(ImageInitError e){
        outLabel = "";
        outLabel << e.what();
        out->SetLabel(outLabel);
    }
    catch(TTF_InitError e){
        outLabel = "";
        outLabel << e.what();
        out->SetLabel(outLabel);
    }
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

// for singleplayer mode
void cMain::quit(){
    outLabel = "Game Over\nYour Score: ";
    outLabel << game->snake->getScore();
    btn->SetLabel("Restart Singleplayer");

    out->SetLabel(outLabel);
    btn1->Hide();
    btn->Show();
    btn2->Show();
    this->Show();
    game = nullptr;
    t = nullptr;
}
// for multiplayer mode
void cMain::quit(double penaltyPerCentForGameQuitOnMultiPlayer, BodyColor *snake){
    winWidth = 496;
    winHeight = 496;
    outLabel = "Game Over\nRED's Score: ";
    outLabel << game->snake1->getScore();
    outLabel << "\nBLUE's Score: ";
    outLabel << game->snake2->getScore();
    std::string snake_color;
    switch(*snake){
        case RED:
            snake_color = "RED";
            break;
        case BLUE:
            snake_color = "BLUE";
            break;
    }
    outLabel << "\n" << penaltyPerCentForGameQuitOnMultiPlayer << "% penalty applied for " << snake_color;
    delete(snake);
    snake = nullptr;
    btn2->SetLabel("Restart Multiplayer\n(Chaotic Mode)");

    out->SetLabel(outLabel);
    btn1->Hide();
    btn->Show();
    btn2->Show();
    this->Show();
    game = nullptr;
    t = nullptr;
    multiplayer = false;
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