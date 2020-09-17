#include "Game.hpp"

int main() {

  bool again;

  srand(time(NULL));

  do {
    again = false;
    Game game;

    // Menu
    while (game.running() && game.menuRunning) {
      game.menuUpdate();
      game.menuRender();
    }

    if (game.running())
      game.initGame();

    // Game
    while (game.running() && !game.player.dead) {
      game.update();
      game.render();
    }

    // Death screen
    if (game.running())
      game.initDeath();
    while (game.running() && !game.menuRunning) {
      game.deathUpdate();
    }

    if (game.menuRunning && game.running())
      again = true;
  } while (again);

  return 0;
}