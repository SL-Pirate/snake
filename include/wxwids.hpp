#pragma once

#include <wx/wx.h>

#include "main.hpp"
#include "sdl_window.hpp"

class Game;

class cMain : public wxFrame {
public:
    cMain();

    ~cMain() override;

    wxSlider *difficulty = nullptr;
    wxTimer m_timer;

    void pause();

    void quit();

    void quit(double penaltyPerCentForGameQuitOnMultiPlayer, const BodyColor *snake);

private:
    Game *game = nullptr;
    Window *gameWin = nullptr;
    wxButton *btn = nullptr;
    wxButton *btn1 = nullptr;
    wxButton *btn2 = nullptr;
    wxStaticText *out = nullptr;
    wxStaticText *in = nullptr;
    wxString outLabel = "\n\n\tScore goes here";
    static bool multiplayer;

    void startInternal();

    void startSinglePlayer(wxCommandEvent &evt);

    void startMultiplayer(wxCommandEvent &evt);

    void onClose(wxCloseEvent &evt);

    void resume(wxCommandEvent &evt);

    wxDECLARE_EVENT_TABLE();
};


class cApp : public wxApp {
public:
    bool OnInit() override;
};
