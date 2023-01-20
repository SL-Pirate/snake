#pragma once

#include "main.hpp"

class Game;

class cMain : public wxFrame{
    public:
    cMain();

    wxSlider *difficulty = nullptr;
    Game *game = nullptr;

    void pause();
    void quit();

    private:
    wxButton* btn = nullptr;
    wxButton *btn1 = nullptr;
    wxTextCtrl* txt = nullptr;
    wxStaticText* out = nullptr;
    wxStaticText* in = nullptr;
    wxString outLabel = "\n\n\tResult goes here";
    std::thread *t = nullptr;

    void start(wxCommandEvent &evt);
    void onClose(wxCloseEvent &evt);
    void restart(wxCommandEvent &evt);
    void resume(wxCommandEvent &evt);
    static void newGame(cMain *parent);

    wxDECLARE_EVENT_TABLE();
};


class cApp : public wxApp{
    cMain *main;

    public:
    virtual bool OnInit();
};