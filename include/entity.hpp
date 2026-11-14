#pragma once

#include "main.hpp"
#include "graphic_handler.hpp"
#include "sound.hpp"
#include "sdl_window.hpp"

#include <wx/wx.h>
#include <array>
#include <SDL_ttf.h>
#include <random>
#include <memory>

typedef std::vector<std::vector<std::shared_ptr<GraphicItem> > > Arena;
typedef std::shared_ptr<std::array<Dir, NUM_CHAINED_MOVES_ALLOWED> > Moves;

//parent class for all entities snake, wall and food
class Entity {
protected:
    Window *gameWin = nullptr;
    std::shared_ptr<SDL_Texture> texture = nullptr;
    //GraphicItem *arr[ROWS()][COLS()];
    Arena *arr = nullptr;
    //used for passing food entities to set them to null so food can be regenerated if eaten
    std::shared_ptr<GraphicItem> item = nullptr;

public:
    virtual ~Entity() = default;

    Entity();

    //used for passing food entities to set them to null so food can be regenerated if eaten
    virtual void clearItem() {
    }
};

struct FontDeleter {
    void operator()(TTF_Font *ptr) const { TTF_CloseFont(ptr); };
};

//definition of the class Fonts, child of entity
class Fonts : public Entity {
    std::unique_ptr<TTF_Font, FontDeleter> font = nullptr;
    std::shared_ptr<SDL_Rect> dst = nullptr;
    std::string title;
    BodyColor color;

public:
    //int x = horizontal position of the label
    //int y = vertical position of the label
    Fonts(Window *gameWin, const std::string &title, BodyColor color, int x, int y);

    void setTitle(const std::string &pTitle);

    [[nodiscard]] std::shared_ptr<GraphicItem> getItem() const;
};


//definition of the class Snake, child of entity
class Snake : public Entity {
    // const int size = ROWS() * COLS();
    std::vector<std::shared_ptr<GraphicItem> > snake;
    int length = 0;
    Dir dir = right;
    Moves registeredDirs;
    int score = 0;
    wxSlider *difficulty = nullptr;
    std::string scoreTitle;
    std::unique_ptr<Sound> eatSound;
    std::unique_ptr<Sound> dieSound;

    void ate(const std::shared_ptr<GraphicItem> &nextItem);

    [[nodiscard]] Dir getNextDir() const;

public:
    Snake(Window *gameWin, Arena *arr, wxSlider *difficulty, BodyColor color);

    void addToArr() const;

    bool move();

    bool move(const Moves &dirs);

    void setInitialDir(Dir pDir) const;

    [[nodiscard]] int getScore() const;

    void applyPenalty(double penaltyPerCent);

    std::shared_ptr<Fonts> font = nullptr;
    BodyColor color;
};


//definition of the class Wall, child of entity 
class Wall : public Entity {
public:
    Wall(Window *gameWin, Arena *arena);
};


//definition of the class Food, child of entity
class Food : public Entity {
    static std::mt19937 gen;
    std::unique_ptr<Pos> cords = nullptr;

public:
    Food(Window *gameWin, Arena *arr);

    void genFood();

    void clearItem() override;
};

class Pos {
    int x;
    int y;

public:
    Pos(int x, int y);

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;
};
