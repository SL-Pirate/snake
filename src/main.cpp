#include "wxwids.hpp"
#include "game.hpp"
#include "snake.hpp"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(1010, cMain::start)
    EVT_BUTTON(1012, cMain::resume)
    EVT_CLOSE(cMain::onClose)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Snake " VERSION, wxPoint(250, 50), wxSize(400, 400)){
#ifdef _WIN32
    this->SetBackgroundColour(*wxWHITE);
#endif
    this->Center();
    in = new wxStaticText(this, wxID_ANY, "welcome to the Snake Game\nPlease set difficulty:", wxPoint(50, 30), wxSize(300, 100), wxALIGN_CENTER);
    difficulty = new wxSlider(this, 1009, 10, 1, 20, wxPoint(50, 150), wxSize(300, 50));
    btn = new wxButton(this, 1010, "Start", wxPoint(150, 220), wxSize(100, 50));
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
    game = new Game(this);
    t = new std::thread(startGame);
    out->Show();
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
    btn->Hide();
    btn1->Show();
    outLabel = "Your Score: ";
    outLabel << game->snake->getScore();
    out->SetLabel(outLabel);
}
void cMain::startGame(){
    game->start();
}
void cMain::quit(){
    outLabel = "Your Score: ";
    outLabel << game->snake->getScore();
    out->SetLabel(outLabel);
    this->btn->SetLabel("Restart");
    this->btn1->Hide();
    this->btn->Show();
    this->Show();
    game = nullptr;
    t = nullptr;

    SDL_Quit();
}
Game *cMain::game = nullptr;


//Starting point of the program
bool cApp::OnInit(){
    main = new cMain();
    main->Show();

    return true;
}


wxIMPLEMENT_APP_NO_MAIN(cApp);

// #ifdef _WIN32
// int wmain( int argc, wchar_t* argv[] ){
//     if (SDL_Init(SDL_INIT_VIDEO) < 0){
//         // std::cout << "Error: SDL INIT VIDEO FAILED!" << SDL_GetError() << std::endl;
//     }
//     if (!IMG_Init(IMG_INIT_PNG)){
//         // std::cout << "SDL_IMG INIT FAILED! Error: " << SDL_GetError() << std::endl;
//     }
//     if (TTF_Init() == -1){
//         // std::cout << "TTF INIT FAILED! Error: " << TTF_GetError() << std::endl;
//     }

//     return wxEntry(argc, argv);
// }
// #else
int main(int argc, char** argv){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        // std::cout << "Error: SDL INIT VIDEO FAILED!" << SDL_GetError() << std::endl;
    }

    return wxEntry(argc, argv);
}
// #endif