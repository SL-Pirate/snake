#include <wx/wx.h>

#include "entity.hpp"
#include "sdl_window.hpp"

#include "game.hpp"

// Definition of class "Entity"
// which is the parent class for all entities snke, wall and food
Entity::Entity() = default;

Entity::~Entity() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

// definition of the actual "Snake" class
Snake::Snake(Window *gameWin, Arena *arr, wxSlider *difficulty, const BodyColor color) {
    this->gameWin = gameWin;
    this->arr = arr;
    this->color = color;
    snake = std::vector<std::shared_ptr<GraphicItem> >(ROWS() * COLS());
    eatSound = std::make_unique<Sound>("sfx/boom.wav");
    dieSound = std::make_unique<Sound>("sfx/aaaugh.wav");
    this->registeredDirs = std::make_shared<std::array<Dir, NUM_CHAINED_MOVES_ALLOWED> >();
    setInitialDir(right);

    const char *filePath;

    if (color == RED) {
        filePath = "gfx/red.png";
        texture = gameWin->loadTexture(openRes(filePath)); // res/gfx/body.png
        snake[0] = std::make_shared<GraphicItem>(texture, ROWS() / 2, COLS() / 2, SNAKE);
        snake[1] = std::make_shared<GraphicItem>(texture, ROWS() / 2 + 1, COLS() / 2, SNAKE);

        // display scores
        scoreTitle = "Arrows: ";
        font = std::make_shared<Fonts>(
            gameWin,
            scoreTitle + std::to_string(score),
            color,
            winWidth / 4 - 50,
            winHeight
        );
    } else if (color == BLUE) {
        dir = left;
        filePath = "gfx/blue.png";
        texture = gameWin->loadTexture(openRes(filePath)); // res/gfx/body.png
        snake[0] = std::make_shared<GraphicItem>(texture, ROWS() / 2, COLS() / 2 + 1, SNAKE);
        snake[1] = std::make_shared<GraphicItem>(texture, ROWS() / 2 + 1, COLS() / 2 + 1, SNAKE);

        // display scores
        scoreTitle = "WASD: ";
        font = std::make_shared<Fonts>(
            gameWin,
            scoreTitle + std::to_string(score),
            color,
            winWidth * 3 / 4 - 50,
            winHeight
        );
    }

    this->difficulty = difficulty;
    length = 2;
}

void Snake::addToArr() const {
    for (int i = 0; i < length; i++) {
        const auto pos = snake[i]->getPos();
        (*arr)[pos->getX()][pos->getY()] = snake[i];
    }
}

bool Snake::move() {
    if (const Dir direction = getNextDir(); dir == left && direction != right || dir == right && direction != left ||
                                            dir == up && direction != down || dir == down && direction != up) {
        dir = direction;
    }

    // deleting the last square where the snake's tail was last in
    const auto pos = snake[length - 1]->getPos();
    (*arr)[pos->getX()][pos->getY()] = nullptr;

    // collision detection
    std::shared_ptr<GraphicItem> nextItem = nullptr;
    const auto pos1 = snake[0]->getPos();
    switch (dir) {
        case up:
            nextItem = (*arr)[pos1->getX()][pos1->getY() - 1];
            break;
        case down:
            nextItem = (*arr)[pos1->getX()][pos1->getY() + 1];
            break;
        case left:
            nextItem = (*arr)[pos1->getX() - 1][pos1->getY()];
            break;
        case right:
            nextItem = (*arr)[pos1->getX() + 1][pos1->getY()];
            break;
        default:
            nextItem = nullptr;
    }
    if (nextItem != nullptr) {
        // Hit the wall (or a snake in that case)
        if (nextItem->id == WALL || nextItem->id == SNAKE) {
            dieSound->play();
            return false;
        }
        // ate food
        if (nextItem->id == FOOD) {
            ate(nextItem);
        }
    } else {
        snake[length - 1] = nullptr;
    }

    for (int i = length - 1; i >= 1; i--) {
        snake[i] = snake[i - 1];
    }
    const auto pos2 = snake[1]->getPos();
    switch (dir) {
        case up:
            snake[0] = std::make_shared<GraphicItem>(texture, pos2->getX(), pos2->getY() - 1, SNAKE);
            break;
        case down:
            snake[0] = std::make_shared<GraphicItem>(texture, pos2->getX(), pos2->getY() + 1, SNAKE);
            break;
        case left:
            snake[0] = std::make_shared<GraphicItem>(texture, pos2->getX() - 1, pos2->getY(), SNAKE);
            break;
        case right:
            snake[0] = std::make_shared<GraphicItem>(texture, pos2->getX() + 1, pos2->getY(), SNAKE);
            break;
        default:
            snake[0] = std::make_shared<GraphicItem>(texture, pos2->getX() + 1, pos2->getY(), SNAKE);
    }

    addToArr();

    return true;
}

bool Snake::move(const Moves &dirs) {
    registeredDirs = dirs;
    return move();
}

Dir Snake::getNextDir() const {
    const Dir currentDir = (*registeredDirs)[0];

    // removing second dir from the list
    for (int i = 1; i < NUM_CHAINED_MOVES_ALLOWED; i++) {
        if ((*registeredDirs)[i] != none) {
            (*registeredDirs)[i - 1] = (*registeredDirs)[i];
        }
    }
    (*registeredDirs)[NUM_CHAINED_MOVES_ALLOWED - 1] = none;

    return currentDir;
}

void Snake::ate(const std::shared_ptr<GraphicItem> &nextItem) {
    length++;
    score += 10 * difficulty->GetValue();

    // delete the food item
    const auto nextPos = nextItem->getPos();
    (*arr)[nextPos->getX()][nextPos->getY()]->rmFromParent();

    // output the score
    font->setTitle(scoreTitle + std::to_string(score));

    // play sound effect
    eatSound->play();
}

void Snake::setInitialDir(const Dir pDir) const {
    (*registeredDirs)[0] = pDir;
    for (int i = 1; i < NUM_CHAINED_MOVES_ALLOWED; i++) {
        (*registeredDirs)[i] = none;
    }
}

void Snake::clearItem() {
    item = nullptr;
}

int Snake::getScore() const {
    return score;
}

// apply a penalty for defined amount to the score as a percentage
void Snake::applyPenalty(const double penaltyPerCent) {
    score -= static_cast<int>(score * penaltyPerCent / 100.0);
}
