#pragma once

#include <enet/enet.h>
#include <wx/wx.h>

#include "main.hpp"
#include "sdl_window.hpp"

class Game;

class cMain : public wxFrame {
public:
    cMain();

    wxSlider *difficulty = nullptr;
    wxTimer m_timer;
    wxTimer m_player_discover;

    void pause();

    void quit();

    void quit(double penaltyPerCentForGameQuitOnMultiPlayer, const std::shared_ptr<BodyColor> &snake);

    void discoverPlayers(wxTimerEvent &evt);

private:
    std::unique_ptr<Game> game = nullptr;
    std::shared_ptr<Window> gameWin = nullptr;
    wxButton *singlePlayerButton = nullptr;
    wxButton *resumeButton = nullptr;
    wxButton *chaoticModeButton = nullptr;
    wxButton *onlineMultiplayerButton = nullptr;
    wxFrame *multiplayerRoom = nullptr;
    wxStaticText *roomCode = nullptr;
    wxButton *multiplayerRoomStartButton = nullptr;
    wxButton *createRoomButton = nullptr;
    wxButton *joinRoomButton = nullptr;
    wxListBox *playerList = nullptr;
    wxStaticText *out = nullptr;
    wxStaticText *in = nullptr;
    wxString outLabel = "\n\n\tScore goes here";
    wxString roomCodeLabel = "Room Code: ----";
    wxTextCtrl *yourName = nullptr;
    wxTextCtrl *roomCodeInput = nullptr;

    void startInternal();

    void startSinglePlayer(wxCommandEvent &evt);

    void startChaotic(wxCommandEvent &evt);

    void startOnlineMultiplayer(wxCommandEvent &evt);

    void joinOnlineMultiplayer(wxCommandEvent &evt);

    void showConnectionWindow(wxCommandEvent &evt);

    void onClose(wxCloseEvent &evt);

    void resume(wxCommandEvent &evt);

    wxDECLARE_EVENT_TABLE();
};

class cApp : public wxApp {
public:
    bool OnInit() override;
};
