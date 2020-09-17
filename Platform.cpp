#include "Platform.hpp"

Platform::Platform() {
  platTex.loadFromFile("src/Textures/platform3.png");
  platSprite.setTexture(platTex);
  platSprite.setScale(sf::Vector2f(1.f, 1.f));
}

Platform::~Platform() {}

void Platform::initPlatform(int i) {
  platSprite.setPosition(rand() % 550 + 120, 30 + (100 * i));
}

void Platform::reinitPlatform() {
  platSprite.setPosition(rand() % 550 + 120,
                         -platSprite.getGlobalBounds().height);
}

void Platform::update(Player *player, sf::RenderTarget *target) {
  player->playerBounds = player->sprite.getGlobalBounds();

  if (player->isStart)
    clock.restart();

  currTime = clock.getElapsedTime();
  if (currTime.asSeconds() > prevTime.asSeconds() + 7 && !player->isStart &&
      currTime.asSeconds() < 150) {
    prevTime = currTime;
    accel += 0.5;
  }

  if (player->playerBounds.top <= 25)
    playerOut = 5.5;

  platSprite.move(0.f, vel + accel + playerOut);
  platBound = platSprite.getGlobalBounds();

  if (playerOut > 0)
    playerOut -= 1.5;
  else
    playerOut = 0;
}

void Platform::render(sf::RenderTarget *target) { target->draw(platSprite); }