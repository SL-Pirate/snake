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
    in = new wxStaticText(this, wxID_ANY, "welcome to the Snake Game\nPlease set difficulty:", wxPoint(50, 75), wxSize(300, 200));
    difficulty = new wxSlider(this, 1009, 10, 1, 20, wxPoint(50, 150), wxSize(300, 50));
    btn = new wxButton(this, 1010, "Start", wxPoint(150, 220), wxSize(100, 50));
    difficulty->SetName("Difficulty");
    btn1 = new wxButton(this, 1012, "Resume", wxPoint(150, 220), wxSize(100, 50));
    btn1->Hide();
    out = new wxStaticText(this, wxID_ANY, outLabel, wxPoint(50, 290), wxSize(300, 140), wxALIGN_CENTER_HORIZONTAL);
    out->Hide();
}
cMain::~cMain(){
    delete(difficulty);
    delete(game);
    delete(btn);
    delete(btn1);
    delete(txt);
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
}
Game *cMain::game = nullptr;


//Starting point of the program
bool cApp::OnInit(){
    main = new cMain();
    main->Show();

    return true;
}

wxIMPLEMENT_APP(cApp);