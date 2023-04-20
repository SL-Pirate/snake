#pragma once

#include "main.hpp"

class Game;

class cMain : public wxFrame{
    public:
    cMain();
    ~cMain();

    wxSlider *difficulty = nullptr;
    static Game *game;

    void pause();
    void quit();
    void quit(double penaltyPerCentForGameQuitOnMultiPlayer, BodyColor *snake);

    private:
    wxButton* btn = nullptr;
    wxButton *btn1 = nullptr;
    wxButton *btn2 = nullptr;
    wxStaticText* out = nullptr;
    wxStaticText* in = nullptr;
    wxString outLabel = "\n\n\tScore goes here";
    std::thread *t = nullptr;
    static bool multiplayer;

    void start(wxCommandEvent &evt);
    void startMultiplayer(wxCommandEvent &evt);
    void onClose(wxCloseEvent &evt);
    void resume(wxCommandEvent &evt);
    static void startGame();

    wxDECLARE_EVENT_TABLE();
};


class cApp : public wxApp{
    cMain *main;

    public:
    virtual bool OnInit();
};