#include "wxwids.hpp"
#include "game.hpp"

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
    out = new wxStaticText(this, wxID_ANY, outLabel, wxPoint(50, 290), wxSize(300, 140));
    out->Hide();
}

void cMain::start(wxCommandEvent &evt){
    this->Hide();
    t = new std::thread(newGame, this);
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
}
void cMain::newGame(cMain *parent){
    parent->game = new Game(parent);
}
void cMain::quit(){
    this->btn->SetName("Restart");
    this->Show();
    game = nullptr;
    t = nullptr;
}


//Starting point of the program
bool cApp::OnInit(){
    main = new cMain();
    main->Show();

    return true;
}

wxIMPLEMENT_APP(cApp);