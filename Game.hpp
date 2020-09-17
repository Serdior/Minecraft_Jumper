#ifndef GAME_H
#define GAME_H

#include "Platform.hpp"
#include "Player.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <fstream>
#include <iostream>

#define NUM 8

class Game {
private:
  sf::VideoMode videoMode;
  sf::Event event;
  sf::Texture bgTex, towerTex, interfaceTex, menuTex;
  sf::Sprite bg, tower, interface, menu;

  sf::FloatRect playerBounds;
  sf::FloatRect platformBounds;

  sf::Font font;
  std::string bestStr;
  sf::Text points, best, timeText, over, press;
  std::ifstream file;
  std::ofstream fileOf;
  sf::Clock clock;
  sf::Time time, prevTime;

  Platform platform[NUM];

  void pointsUpdate();
  void changeTower();

  bool inMenu = true;
  int pointsNum = 0;

public:
  Game();
  virtual ~Game();

  const bool running();

  Player player;
  sf::RenderWindow *window;

  bool platformCollision(Player *player, Platform *platform);
  void pollEvents();
  void initGame();
  void initDeath();
  void deathUpdate();

  bool menuRunning = true;
  bool dead = false;

  void update();
  void render();
  void timeUpdate();
  void menuUpdate();
  void menuRender();
};
#endif
