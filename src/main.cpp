#include "wxwids.hpp"
#include "game.hpp"
#include "entity.hpp"
#include "error.hpp"
#include "sdl_window.hpp"
#include "main.hpp"

#include <SDL_image.h>
#include <thread>
#include <random>
#include <wx/wx.h>

#include "network.hpp"

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw SDL_InitError();
    }

    return wxEntry(argc, argv);
}

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(1010, cMain::startSinglePlayer)
    EVT_BUTTON(1011, cMain::startChaotic)
    EVT_BUTTON(1013, cMain::showConnectionWindow)
    EVT_BUTTON(1015, cMain::startOnlineMultiplayer)
    EVT_BUTTON(1016, cMain::joinOnlineMultiplayer)
    EVT_BUTTON(1012, cMain::resume)
    EVT_CLOSE(cMain::onClose)
wxEND_EVENT_TABLE();

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Snake " VERSION, wxPoint(250, 50), wxSize(400, 400)) {
#ifdef _WIN32
    this->SetBackgroundColour(*wxWHITE);
#endif
    gameWin = std::make_shared<Window>("Snake", winHeight + GAME_SCREEN_SCORE_HEIGHT_OFFSET, winWidth);
    gameWin->hide();
    game = std::make_unique<Game>(this, gameWin);
    this->Center();
    in = new wxStaticText(
        this,
        wxID_ANY,
        "welcome to the Snake Game\nPlease set difficulty:",
        wxPoint(50, 30),
        wxSize(300, 50),
        wxALIGN_CENTER
    );
    difficulty = new wxSlider(this, 1009, 10, 1, 20, wxPoint(50, 100), wxSize(300, 50));
    singlePlayerButton = new wxButton(this, 1010, "Start Singleplayer", wxPoint(33, 170), wxSize(150, 50));
    chaoticModeButton = new wxButton(
        this,
        1011,
        "Start Multiplayer\n(Chaotic Mode)",
        wxPoint(217, 170),
        wxSize(150, 70)
    );
    onlineMultiplayerButton = new wxButton(this, 1013, "Start Online Multiplayer", wxPoint(120, 270), wxSize(160, 50));
    resumeButton = new wxButton(this, 1012, "Resume", wxPoint(150, 220), wxSize(100, 50));
    resumeButton->Hide();
    out = new wxStaticText(this, wxID_ANY, outLabel, wxPoint(50, 330), wxSize(300, 140), wxALIGN_CENTER);
    out->Hide();

    // connection frame for multiplayer
    multiplayerRoom = new wxFrame(
        this,
        wxID_ANY,
        "Waiting for Players",
        wxDefaultPosition,
        wxSize(400, 440),
        wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT
    );
#ifdef _WIN32
    multiplayerRoom->SetBackgroundColour(*wxWHITE);
#endif
    roomCode = new wxStaticText(
        multiplayerRoom,
        wxID_ANY,
        roomCodeLabel,
        wxPoint(50, 20),
        wxSize(300, 30),
        wxALIGN_CENTER
    );
    new wxStaticText(multiplayerRoom, wxID_ANY, "Your name:", wxPoint(50, 72));
    yourName = new wxTextCtrl(multiplayerRoom, wxID_ANY, "", wxPoint(150, 65), wxSize(200, 30));
    yourName->SetMaxLength(16);
    new wxStaticText(multiplayerRoom, wxID_ANY, "Room code:", wxPoint(50, 117));
    roomCodeInput = new wxTextCtrl(multiplayerRoom, wxID_ANY, "", wxPoint(150, 110), wxSize(200, 30));
    createRoomButton = new wxButton(multiplayerRoom, 1015, "Create Room", wxPoint(50, 160), wxSize(140, 40));
    joinRoomButton = new wxButton(multiplayerRoom, 1016, "Join Room", wxPoint(210, 160), wxSize(140, 40));
    new wxStaticText(multiplayerRoom, wxID_ANY, "Players:", wxPoint(50, 215));
    playerList = new wxListBox(multiplayerRoom, wxID_ANY, wxPoint(50, 240), wxSize(300, 90));
    multiplayerRoomStartButton = new wxButton(multiplayerRoom, 1014, "Start", wxPoint(150, 345), wxSize(100, 40));
    // nothing to start until players have joined a room
    multiplayerRoomStartButton->Disable();
    // default close destroys the frame and leaves multiplayerRoom dangling
    multiplayerRoom->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent &) { multiplayerRoom->Hide(); });
    multiplayerRoom->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent &evt) {
        m_player_discover.Stop();
        evt.Skip();
    });
    multiplayerRoom->Bind(wxEVT_TIMER, &cMain::discoverPlayers, this, m_player_discover.GetId());
}

// ReSharper disable once CppMemberFunctionMayBeConst
void cMain::showConnectionWindow(wxCommandEvent &) {
    multiplayerRoom->CenterOnParent();
    multiplayerRoom->Show();
    multiplayerRoom->Raise();
    m_player_discover.Start(2500);
}

void cMain::startInternal() {
    try {
        singlePlayerButton->Hide();
        chaoticModeButton->Hide();
        onlineMultiplayerButton->Hide();
        resumeButton->Show();
        out->Show();
        this->Hide();
        gameWin->show();

        if (game->gameMode == CHAOTIC) {
            game->startChaotic();
        } else if (game->gameMode == SINGLE_PLAYER) {
            game->startSingleplayer();
        } else if (game->gameMode == MULTIPLAYER) {
            game->startMultiPlayer();
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
    game->gameMode = SINGLE_PLAYER;
    winHeight = 496;
    winWidth = 496;
    gameWin->resize(winHeight + GAME_SCREEN_SCORE_HEIGHT_OFFSET, winWidth);
    startInternal();
}

void cMain::startChaotic(wxCommandEvent &) {
    game->gameMode = CHAOTIC;
    winWidth = 592;
    winHeight = 592;
    gameWin->resize(winHeight + GAME_SCREEN_SCORE_HEIGHT_OFFSET, winWidth);
    startInternal();
}

void cMain::joinOnlineMultiplayer(wxCommandEvent &) {
    if (!game->network.initialize()) {
        out->SetLabel("Error initializing network stack");
        out->Show();
        return;
    }

    if (!game->network.createClient()) {
        out->SetLabel("Error creating client");
        out->Show();
        return;
    }

    const std::string sessionId = roomCodeInput->GetValue().Trim().Trim(false).ToStdString();
    const auto name = yourName->GetValue().Trim().Trim(false).ToStdString();
    if (sessionId.empty()) {
        out->SetLabel("Please enter the session id or start a session");
        out->Show();
        return;
    }
    if (name.empty()) {
        out->SetLabel("Please enter the name of the room");
        out->Show();
        return;
    }
    if (game->network.connectToSession(sessionId, name)) {
        out->SetLabel("Could not connect to server");
        out->Show();
        return;
    }

    multiplayerRoom->Hide();
    game->gameMode = MULTIPLAYER;
    winWidth = 592;
    winHeight = 592;
    gameWin->resize(winHeight + GAME_SCREEN_SCORE_HEIGHT_OFFSET, winWidth);
    startInternal();
}

void cMain::startOnlineMultiplayer(wxCommandEvent &evt) {
    if (!game->network.initialize()) {
        out->SetLabel("Error initializing network stack");
        out->Show();
        return;
    }

    if (!game->network.createClient()) {
        out->SetLabel("Error creating client");
        out->Show();
        return;
    }

    const auto sessionId = game->network.createSession();
    if (sessionId->empty()) {
        out->SetLabel("Could not create session");
        out->Show();
        return;
    }
    roomCodeLabel = sessionId.value();

    multiplayerRoom->Hide();
    game->gameMode = MULTIPLAYER;
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
    if (game->gameMode == SINGLE_PLAYER) {
        outLabel = "Your Score: ";
        outLabel << game->snake->getScore();
    } else if (game->gameMode == CHAOTIC) {
        outLabel = "RED's Score: ";
        outLabel << game->snake1->getScore();
        outLabel << "\nBLUE's Score: ";
        outLabel << game->snake2->getScore();
    }
    out->SetLabel(outLabel);
}

// for singleplayer mode
void cMain::quit() {
    if (game->gameMode == MULTIPLAYER) {
        game->network.deinitialize();
    }

    outLabel = "Game Over\nYour Score: ";
    outLabel << game->snake->getScore();
    singlePlayerButton->SetLabel("Restart Singleplayer");

    out->SetLabel(outLabel);
    resumeButton->Hide();
    singlePlayerButton->Show();
    chaoticModeButton->Show();
    onlineMultiplayerButton->Show();
    this->Show();
    gameWin->hide();
}

// for chaotic mode
void cMain::quit(const double penaltyPerCentForGameQuitOnMultiPlayer, const std::shared_ptr<BodyColor> &snake) {
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
    }
    chaoticModeButton->SetLabel("Restart Multiplayer\n(Chaotic Mode)");

    out->SetLabel(outLabel);
    resumeButton->Hide();
    singlePlayerButton->Show();
    chaoticModeButton->Show();
    onlineMultiplayerButton->Show();
    this->Show();
    gameWin->hide();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void cMain::discoverPlayers(wxTimerEvent &) {
    auto const players = this->game->network.discoverPlayers();
    playerList->Set(players);
}

// Starting point of the program
bool cApp::OnInit() {
    const auto main = new cMain();
    main->Show();
    return true;
}

wxIMPLEMENT_APP_NO_MAIN(cApp);
