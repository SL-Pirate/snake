# RAII refactor todo

In order of implementation.

## Steps

- [x] **1. Entities owned by `Game`**: `foods`, `snake`, `snake1`, `snake2`, `wall`
    - Where: `include/game.hpp`, `src/game.cpp`
    - Convert to: `std::vector<std::unique_ptr<Food>>`, `std::unique_ptr<Snake>`, `std::unique_ptr<Wall>`
    - Note: `src/main.cpp:158` deletes a snake from outside `Game`. Decide the owner first.
    - Note: `arr` must stay declared before the entities in `Game` (members are destroyed in reverse order).

- [x] **2. `Snake` members**: `font`, `eatSound`, `dieSound`
    - Where: `src/snake.cpp:21-22`, `:36`, `:46`
    - Convert to: `std::unique_ptr`, or plain members
    - Fixes: `eatSound` and `dieSound` are never deleted (leak).

- [x] **3. Direction arrays**: `registeredDirs` in `Snake`, `dirs` in `Game`
    - Where: `src/snake.cpp:23`, `src/game.cpp:370`
    - Convert to: `std::array` or `std::vector<Dir>`
    - Fixes: `src/snake.cpp:134` uses `delete` on an array (needs `delete[]`).

- [ ] **4. Local heap values**: `snake1_moved`, `snake2_moved`, `culpritSnake`
    - Where: `src/game.cpp:169-170`, `:244`, `:249`
    - Convert to: plain `bool`, and `std::optional<BodyColor>`

- [ ] **5. `emptyCords`**
    - Where: `src/food.cpp:30-60`
    - Convert to: `std::vector<std::array<int, 2>>`

- [ ] **6. `GraphicItem` internals**: `org`, `dst`, `pos`, and `dst` in `Fonts`
    - Where: `src/graphic_handler.cpp`, `src/fonts.cpp:19`
    - Convert to: `SDL_Rect` by value. `getPos()` returns `std::array<int, 2>`.
    - Fixes: `getPos()` uses `delete` on an array at `src/graphic_handler.cpp:61`.
    - Goal: `~GraphicItem` becomes empty.

- [ ] **7. `SDL_Texture`**: entity textures, `Game::background`, font texture
    - Where: `src/snake.cpp:11`, `src/game.cpp:321`, `src/fonts.cpp:37`
    - Convert to: `std::unique_ptr` with a custom deleter (`SDL_DestroyTexture`)

- [ ] **8. `TTF_Font` in `Fonts`**
    - Where: `src/fonts.cpp:14`
    - Convert to: `std::unique_ptr` with a custom deleter (`TTF_CloseFont`)
    - Fixes: the font is never closed (leak).

- [ ] **9. `Sound` and `Window` classes** (rule of five)
    - Where: `src/sound.cpp`, `src/sdl_window.cpp`
    - Keep the destructors. Delete copy constructor and copy assignment.
    - Why: a copy would free the resource twice.

- [ ] **10. `game`, `gameWin` in `cMain`**
    - Where: `src/main.cpp:33-35`, `:50-51`
    - Convert to: `std::unique_ptr`
    - Note: lifetime is tricky here (`delete (this)` at `src/main.cpp:107`).

## Do not convert

- wx widgets in `src/main.cpp:37-44`. The parent window owns its children and deletes them.
  The manual deletes at `src/main.cpp:49-55` look risky for the same reason.

## Other bugs seen

- [ ] `Snake::ate()`: check that `rmFromParent()` really releases the eaten food's `shared_ptr`.
