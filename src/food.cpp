#include "entity.hpp"
#include "error.hpp"

std::mt19937 Food::gen{std::random_device{}()};

Food::Food(Window *gameWin, Arena *arr) {
    this->arr = arr;
    this->gameWin = gameWin;
    texture = gameWin->loadTexture(openRes("gfx/egg.png"));

    genFood();
}

void Food::genFood() {
    if (item == nullptr) {
        int len_emptyCords = 0;

        for (int i = 0; i < ROWS(); i++) {
            for (int j = 0; j < COLS(); j++) {
                if ((*arr)[i][j] == nullptr) {
                    len_emptyCords++;
                }
            }
        }

        if (len_emptyCords == 0) {
            throw GridSpaceFullError();
        }

        auto emptyCords = std::vector<std::unique_ptr<Pos> >(len_emptyCords);
        int index_emptyCords = 0;

        for (int i = 0; i < ROWS(); i++) {
            for (int j = 0; j < COLS(); j++) {
                if ((*arr)[i][j] == nullptr) {
                    emptyCords[index_emptyCords] = std::make_unique<Pos>(i, j);
                    index_emptyCords++;

                    if (index_emptyCords == len_emptyCords) {
                        break;
                    }
                }
            }
        }

        std::uniform_int_distribution distrib(0, len_emptyCords - 1);
        const int lucky_index = distrib(gen);

        cords = std::move(emptyCords[lucky_index]);

        // item = new GraphicItem(texture, cords[0], cords[1], FOOD, this);
        item = std::make_shared<GraphicItem>(texture, cords->getX(), cords->getY(), FOOD, this);
        (*arr)[cords->getX()][cords->getY()] = item;
    }
}

void Food::clearItem() {
    item = nullptr;
}
