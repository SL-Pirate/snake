#include "game.hpp"
#include "sdl_window.hpp"
#include "entity.hpp"
#include "error.hpp"
#include "sound.hpp"

Game::Game(cMain *parent, Window *gameWin)
{
    this->parent = parent;
    this->gameWin = gameWin;
    if (!IMG_Init(IMG_INIT_PNG))
    {
        throw ImageInitError();
    }
    if (TTF_Init() == -1)
    {
        throw TTF_InitError();
    }
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        Sound::hasSound = false;
    }
    else
    {
        Sound::hasSound = true;
    }
}

void Game::startSingleplayer()
{
    background = gameWin->loadTexture(openRes("gfx/grass-pattern.jpg")); // res/gfx/grass-pattern.jpg
    foods = new Food *[numFoodItemsSinglePlayer];

    // arr[ROWS()][COLS()]
    // equates to arr[y][x]
    arr = new GraphicItem **[ROWS()];
    for (int i = 0; i < ROWS(); i++)
    {
        arr[i] = new GraphicItem *[COLS()];
    }

    for (int i = 0; i < ROWS(); i++)
    {
        for (int j = 0; j < COLS(); j++)
        {
            arr[i][j] = nullptr;
        }
    }

    wall = new Wall(gameWin, arr);

    // implementing snake & food
    snake = new Snake(gameWin, arr, parent->difficulty /*1000/parent->difficulty->GetValue()*/, RED);
    for (int i = 0; i < numFoodItemsSinglePlayer; i++)
    {
        foods[i] = new Food(gameWin, arr);
    }

    parent->m_timer.Bind(wxEVT_TIMER, &Game::singlePlayerEventHandler, this);
    parent->m_timer.Start(1000 / parent->difficulty->GetValue());
}

void Game::singlePlayerEventHandler(wxTimerEvent &event)
{
    Dir *dirs = resetDirs();
    while (SDL_PollEvent(&evnt))
    {
        if (evnt.type == SDL_QUIT)
        {
            stopGame(false);
        }
        else if (evnt.type == SDL_KEYDOWN)
        {
            switch (evnt.key.keysym.sym)
            {
            case SDLK_UP:
                isKeyPressed = true;
                setDir(up, dirs);
                break;
            case SDLK_DOWN:
                isKeyPressed = true;
                setDir(down, dirs);
                break;
            case SDLK_LEFT:
                isKeyPressed = true;
                setDir(left, dirs);
                break;
            case SDLK_RIGHT:
                isKeyPressed = true;
                setDir(right, dirs);
                break;
            case SDLK_ESCAPE:
                isKeyPressed = true;
                isPaused = true;
                parent->pause();
                break;
            case SDLK_q:
                stopGame(false);
            }
        }
    }

    gameWin->clearRen();

    bool canKeepGoing = true;
    // move the snake
    if (isKeyPressed)
    {
        if (!isPaused)
        {
            canKeepGoing = snake->move(dirs);
            dirs = resetDirs();
            isKeyPressed = false;
        }
    }
    else
    {
        canKeepGoing = snake->move();
    }

    // refresh food
    try
    {
        for (int i = 0; i < numFoodItemsSinglePlayer; i++)
        {
            foods[i]->genFood();
        }
    }
    catch (GridSpaceFullError e)
    {
        canKeepGoing = false;
    }

    // displaying everything on screen
    gameWin->render(background);
    gameWin->render((snake->font->getItem()));
    for (int i = 0; i < ROWS(); i++)
    {
        for (int j = 0; j < COLS(); j++)
        {
            if (arr[i][j] != nullptr)
            {
                gameWin->render(arr[i][j]);
            }
        }
    }

    if (!canKeepGoing)
    {
        stopGame(false);
    }
    gameWin->display();
}

void Game::startMultiplayer()
{
    background = gameWin->loadTexture(openRes("gfx/grass-pattern.jpg")); // res/gfx/grass-pattern.jpg
    foods = new Food *[numFoodItemsMultiPlayer];

    // arr[ROWS()][COLS()]
    // equates to arr[y][x]
    arr = new GraphicItem **[ROWS()];
    for (int i = 0; i < ROWS(); i++)
    {
        arr[i] = new GraphicItem *[COLS()];
    }

    for (int i = 0; i < ROWS(); i++)
    {
        for (int j = 0; j < COLS(); j++)
        {
            arr[i][j] = nullptr;
        }
    }

    wall = new Wall(gameWin, arr);

    // implementing snake & food
    snake1 = new Snake(gameWin, arr, parent->difficulty /*1000/parent->difficulty->GetValue()*/, RED);
    snake2 = new Snake(gameWin, arr, parent->difficulty /*1000/parent->difficulty->GetValue()*/, BLUE);
    snake2->setInitialDir(left);
    for (int i = 0; i < numFoodItemsMultiPlayer; i++)
    {
        foods[i] = new Food(gameWin, arr);
    }

    parent->m_timer.Bind(wxEVT_TIMER, &Game::multiPlayerEventHandler, this);
    parent->m_timer.Start(1000 / parent->difficulty->GetValue());
}

void Game::multiPlayerEventHandler(wxTimerEvent &event)
{
    Dir *dir1 = resetDirs();
    Dir *dir2 = resetDirs();

    bool *snake1_moved = new bool(false);
    bool *snake2_moved = new bool(false);

    while (SDL_PollEvent(&evnt))
    {
        if (evnt.type == SDL_QUIT)
        {
            stopGame(true);
        }
        else if (evnt.type == SDL_KEYDOWN)
        {
            switch (evnt.key.keysym.sym)
            {
            case SDLK_UP:
                isKeyPressed = true;
                setDir(up, dir1, snake1_moved);
                break;
            case SDLK_DOWN:
                isKeyPressed = true;
                setDir(down, dir1, snake1_moved);
                break;
            case SDLK_LEFT:
                isKeyPressed = true;
                setDir(left, dir1, snake1_moved);
                break;
            case SDLK_RIGHT:
                isKeyPressed = true;
                setDir(right, dir1, snake1_moved);
                break;
            case SDLK_w:
                isKeyPressed = true;
                setDir(up, dir2, snake2_moved);
                break;
            case SDLK_s:
                isKeyPressed = true;
                setDir(down, dir2, snake2_moved);
                break;
            case SDLK_a:
                isKeyPressed = true;
                setDir(left, dir2, snake2_moved);
                break;
            case SDLK_d:
                isKeyPressed = true;
                setDir(right, dir2, snake2_moved);
                break;
            case SDLK_ESCAPE:
                isKeyPressed = true;
                isPaused = true;
                parent->pause();
                break;
            case SDLK_q:
                stopGame(true);
            }
        }
    }

    gameWin->clearRen();

    // move the snake
    bool canKeepGoing = true;
    if (isKeyPressed)
    {
        if (!isPaused)
        {
            if (*snake1_moved)
            {
                canKeepGoing = snake1->move(dir1);
                *snake1_moved = false;
                dir1 = resetDirs();
            }

            if (*snake2_moved)
            {
                canKeepGoing = snake2->move(dir2);
                *snake2_moved = false;
                dir2 = resetDirs();
            }
            isKeyPressed = false;
        }
    }
    else
    {
        if (!snake1->move())
        {
            snake1->applyPenalty(penaltyPerCentForGameQuitOnMultiPlayer);
            culpritSnake = new BodyColor(snake1->color);
            canKeepGoing = false;
        }
        if (!snake2->move())
        {
            snake2->applyPenalty(penaltyPerCentForGameQuitOnMultiPlayer);
            culpritSnake = new BodyColor(snake2->color);
            canKeepGoing = false;
        }
    }

    // refresh food
    try
    {
        for (int i = 0; i < numFoodItemsMultiPlayer; i++)
        {
            foods[i]->genFood();
        }
    }
    catch (GridSpaceFullError)
    {
        canKeepGoing = false;
    }

    // displaying everything on screen
    gameWin->render(background);
    gameWin->render((snake1->font->getItem()));
    gameWin->render((snake2->font->getItem()));
    for (int i = 0; i < ROWS(); i++)
    {
        for (int j = 0; j < COLS(); j++)
        {
            if (arr[i][j] != nullptr)
            {
                gameWin->render(arr[i][j]);
            }
        }
    }

    if (!canKeepGoing)
    {
        stopGame(true);
    }

    gameWin->display();
}

void Game::stopGame(bool isMultiplayer)
{
    if (parent->m_timer.IsRunning())
    {
        parent->m_timer.Stop();
    }

    if (isMultiplayer)
    {
        // waiting for the game over music to finish (only if exists)
        if (Sound::hasSound)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        gameWin->clearRen();
        parent->quit(penaltyPerCentForGameQuitOnMultiPlayer, culpritSnake);
        for (int i = 0; i < numFoodItemsMultiPlayer; i++)
        {
            delete (foods[i]);
            foods[i] = nullptr;
        }
        delete[] foods;
        foods = nullptr;
    }
    else
    {
        // waiting for the game over music to finish (only if exists)
        if (Sound::hasSound)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        gameWin->clearRen();
        parent->quit();
        for (int i = 0; i < numFoodItemsSinglePlayer; i++)
        {
            delete (foods[i]);
            foods[i] = nullptr;
        }
        delete[] foods;
        foods = nullptr;
    }
}

Game::~Game()
{
    gameWin->hide();
    gameWin = nullptr;
    SDL_DestroyTexture(background);
    background = nullptr;
    // DO NOT free graphic items from anywhere else since they will be already freed from here
    for (int i = 0; i < ROWS(); i++)
    {
        for (int j = 0; j < COLS(); j++)
        {
            delete (arr[i][j]);
        }
        delete (arr[i]);
    }
    delete (arr);
    arr = nullptr;
    delete (snake);
    snake = nullptr;
    delete (snake1);
    snake1 = nullptr;
    delete (snake2);
    snake2 = nullptr;
    delete (wall);
    wall = nullptr;

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Game::resume()
{
    isPaused = false;
    isKeyPressed = false;
}

void Game::setDir(Dir currentDir, Dir *dirs)
{
    for (int i = 0; i <= maxNumChainedMovesAllowed; i++)
    {
        if (dirs[i] != none)
        {
            continue;
        }
        else
        {
            dirs[i] = currentDir;
            break;
        }
    }
}

void Game::setDir(Dir currentDir, Dir *dirs, bool *snake_moved)
{
    for (int i = 0; i <= maxNumChainedMovesAllowed; i++)
    {
        if (dirs[i] != none)
        {
            continue;
        }
        else
        {
            dirs[i] = currentDir;
            break;
        }
    }

    *snake_moved = true;
}

Dir *Game::resetDirs()
{
    // setting chained inputs (directions) to none
    Dir *dirs = new Dir[maxNumChainedMovesAllowed];
    for (int i = 0; i < maxNumChainedMovesAllowed; i++)
    {
        dirs[i] = none;
    }

    return dirs;
}
