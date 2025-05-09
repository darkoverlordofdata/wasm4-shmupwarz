#include "corefw/corefw.h" // IWYU pragma: keep
#include "wasm4.h"
#include "game.h"

CFRefPoolRef pool = NULL;
GameRef game;

void start() {
	pool = NewCFRefPool();
    game = NewGame();
    Start(game);

}

void update () {
    Update(game);
    Draw(game);
}
