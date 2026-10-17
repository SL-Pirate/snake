#include "wxwids.hpp"
#include "game.hpp"
#include "entity.hpp"
#include "error.hpp"
#include "sdl_window.hpp"
#include "net_base.hpp"
#include "main.hpp"

#include <SDL_image.h>
#include <thread>
#include <random>
#include <wx/wx.h>

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw SDL_InitError();
        return -1;
    }

    if (enet_initialize() != 0) {
        isNetworkingEnabled = false;
    } else {
        atexit(enet_deinitialize);
    }

    return wxEntry(argc, argv);
}

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(1010, cMain::startSinglePlayer)
    EVT_BUTTON(1011, cMain::startMultiplayer)
    EVT_BUTTON(1012, cMain::resume)
    EVT_CLOSE(cMain::onClose)
wxEND_EVENT_TABLE();

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Snake " VERSION, wxPoint(250, 50), wxSize(400, 400)) {
#ifdef _WIN32
    this->SetBackgroundColour(*wxWHITE);
#endif
    gameWin = new Window("Snake", winHeight + GAME_SCREEN_SCORE_HEIGHT_OFFSET, winWidth);
    gameWin->hide();
    game = game = new Game(this, gameWin);
    this->Center();
    in = new wxStaticText(this, wxID_ANY, "welcome to the Snake Game\nPlease set difficulty:", wxPoint(50, 30),
                          wxSize(300, 50), wxALIGN_CENTER);
    difficulty = new wxSlider(this, 1009, 10, 1, 20, wxPoint(50, 100), wxSize(300, 50));
    btn = new wxButton(this, 1010, "Start Singleplayer", wxPoint(33, 170), wxSize(150, 50));
    btn2 = new wxButton(this, 1011, "Start Multiplayer\n(Chaotic Mode)", wxPoint(217, 170), wxSize(150, 70));
    btn1 = new wxButton(this, 1012, "Resume", wxPoint(150, 220), wxSize(100, 50));
    btn1->Hide();
    out = new wxStaticText(this, wxID_ANY, outLabel, wxPoint(50, 290), wxSize(300, 140), wxALIGN_CENTER);
    out->Hide();
}

cMain::~cMain() {
    delete (difficulty);
    delete (game);
    delete (gameWin);
    delete (btn);
    delete (btn1);
    delete (out);
    delete (in);
}

void cMain::startInternal() {
    try {
        btn->Hide();
        btn2->Hide();
        btn1->Show();
        out->Show();
        this->Hide();
        gameWin->show();

        if (multiplayer) {
            game->startMultiplayer();
        } else {
            game->startSingleplayer();
        }
    } catch (ImageInitError &e) {
        outLabel = "";
        outLabel << e.what();
        out->SetLabel(outLabel);
    } catch (TTF_InitError &e) {
        outLabel = "";
        outLabel << e.what();
        out->SetLabel(outLabel);
    }
}

void cMain::startSinglePlayer(wxCommandEvent &) {
    multiplayer = false;
    winHeight = 496;
    winWidth = 496;
    gameWin->resize(winHeight + GAME_SCREEN_SCORE_HEIGHT_OFFSET, winWidth);
    startInternal();
}

void cMain::startMultiplayer(wxCommandEvent &) {
    multiplayer = true;
    winWidth = 592;
    winHeight = 592;
    gameWin->resize(winHeight + GAME_SCREEN_SCORE_HEIGHT_OFFSET, winWidth);
    startInternal();
}

void cMain::resume(wxCommandEvent &) {
    this->Hide();
    gameWin->show();
    game->resume();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void cMain::onClose(wxCloseEvent &) {
    delete (this);
    exit(EXIT_SUCCESS);
}

void cMain::pause() {
    this->Show();
    gameWin->hide();
    if (!multiplayer) {
        outLabel = "Your Score: ";
        outLabel << game->snake->getScore();
    } else {
        outLabel = "RED's Score: ";
        outLabel << game->snake1->getScore();
        outLabel << "\nBLUE's Score: ";
        outLabel << game->snake2->getScore();
    }
    out->SetLabel(outLabel);
}

// for singleplayer mode
void cMain::quit() {
    outLabel = "Game Over\nYour Score: ";
    outLabel << game->snake->getScore();
    btn->SetLabel("Restart Singleplayer");

    out->SetLabel(outLabel);
    btn1->Hide();
    btn->Show();
    btn2->Show();
    this->Show();
    gameWin->hide();
}

// for multiplayer mode
void cMain::quit(double penaltyPerCentForGameQuitOnMultiPlayer, const BodyColor *snake) {
    outLabel = "Game Over\nRED's Score: ";
    outLabel << game->snake1->getScore();
    outLabel << "\nBLUE's Score: ";
    outLabel << game->snake2->getScore();
    if (snake != nullptr) {
        std::string snake_color;
        switch (*snake) {
            case RED:
                snake_color = "RED";
                break;
            case BLUE:
                snake_color = "BLUE";
                break;
        }
        outLabel << "\n"
                << penaltyPerCentForGameQuitOnMultiPlayer << "% penalty applied for " << snake_color;
        delete (snake);
        snake = nullptr;
    }
    btn2->SetLabel("Restart Multiplayer\n(Chaotic Mode)");

    out->SetLabel(outLabel);
    btn1->Hide();
    btn->Show();
    btn2->Show();
    this->Show();
    gameWin->hide();
}

bool cMain::multiplayer = false;

// Starting point of the program
bool cApp::OnInit() {
    const auto main = new cMain();
    main->Show();
    return true;
}

wxIMPLEMENT_APP_NO_MAIN(cApp);
