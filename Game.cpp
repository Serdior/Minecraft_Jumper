#include "Game.hpp"

Game::Game() {
  videoMode.width = 1024;
  videoMode.height = 768;
  window = new sf::RenderWindow(videoMode, "Minecraft Jumper",
                                sf::Style::Titlebar | sf::Style::Close);
  window->setPosition(sf::Vector2i(400, 0));
  window->setFramerateLimit(60);

  menuTex.loadFromFile("src/Textures/Menu.png");
  menu.setTexture(menuTex);
  menu.setPosition(-215.f, 0.f);
}

void Game::initGame() {

  time = clock.getElapsedTime();
  prevTime = clock.getElapsedTime();

  bgTex.loadFromFile("src/Textures/bg.jpg");
  towerTex.loadFromFile("src/Textures/dirtTower.png");
  interfaceTex.loadFromFile("src/Textures/inter2.png");
  font.loadFromFile("src/Minecraft.ttf");

  bg.setTexture(bgTex);
  bg.setPosition(-100.f, 0.f);
  tower.setTexture(towerTex);
  tower.setPosition(70.f, 0.f);
  interface.setTexture(interfaceTex);
  interface.setPosition(820.f, 370.f);

  file.open("src/best.txt");
  file >> bestStr;
  file.close();

  best.setString(bestStr);
  best.setPosition(850.f, 515.f);
  best.setCharacterSize(30);
  best.setFont(font);

  points.setString(std::to_string(pointsNum));
  points.setPosition(850.f, 435.f);
  points.setCharacterSize(30);
  points.setFont(font);

  for (int i = 0; i < NUM; i++)
    for (int j = 0; j <= i; j++)
      platform[i].initPlatform(i);
}

void Game::initDeath() {
  over.setString("Game Over");
  over.setPosition(320.f, 350.f);
  over.setCharacterSize(80);
  over.setFont(font);

  press.setString("Press Enter to start again");
  press.setPosition(360.f, 450.f);
  press.setCharacterSize(30);
  press.setFont(font);

  if (pointsNum > stoi(bestStr)) {
    fileOf.open("src/best.txt");
    fileOf << std::to_string(pointsNum);
    fileOf.close();
  }
}

Game::~Game() { delete window; }

const bool Game::running() { return window->isOpen(); }

void Game::pollEvents() {
  while (window->pollEvent(event)) {
    switch (event.type) {
    case sf::Event::KeyPressed:
      if (event.key.code == sf::Keyboard::Escape)
        window->close();
      break;
    }
    if (event.type == sf::Event::Closed)
      window->close();
  }
}

bool Game::platformCollision(Player *player, Platform *platform) {
  playerBounds = player->sprite.getGlobalBounds();
  platformBounds = platform->platSprite.getGlobalBounds();

  if (!player->jumping && playerBounds.intersects(platformBounds) &&
      (playerBounds.top + platformBounds.height -
           (player->vel.y - platform->vel) <=
       platformBounds.top) &&
      (playerBounds.left + playerBounds.width - 17 > platformBounds.left) &&
      (playerBounds.left + 6 < platformBounds.left + platformBounds.width)) {
    player->sprite.setPosition(playerBounds.left,
                               platformBounds.top - playerBounds.height);
    return 1;
  }
  return 0;
}

void Game::update() {
  pollEvents();
  timeUpdate();
  pointsUpdate();
  changeTower();

  player.update(window);
  player.onGround = false;
  for (int i = 0; i < NUM; i++)
    for (int j = 0; j < NUM; j++)
      if ((platform[i].platBound.top >= window->getSize().y && i != j))
        platform[i].reinitPlatform();

  for (int i = 0; i < NUM; i++) {
    if (!player.isStart)
      platform[i].vel = PlatVel;
    platform[i].update(&player, window);
    if (platformCollision(&player, &platform[i]) || player.isStart)
      player.onGround = true;
  }

  if (player.isStart)
    clock.restart();
}

void Game::menuUpdate() {
  pollEvents();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    menuRunning = false;
}

void Game::timeUpdate() {
  time = clock.getElapsedTime();
  timeText.setString(std::to_string((int)time.asSeconds()));
  timeText.setPosition(850.f, 590.f);
  timeText.setCharacterSize(30);
  timeText.setFont(font);
}

void Game::pointsUpdate() {
  if (time.asSeconds() - prevTime.asSeconds() > 1) {
    pointsNum += 500;
    prevTime = time;
  }
  if (player.sprite.getGlobalBounds().top +
          player.sprite.getGlobalBounds().height / 2 <=
      0)
    pointsNum += 10;

  points.setString(std::to_string(pointsNum));

  if (pointsNum > std::stoi(bestStr)) {
    best.setString(std::to_string(pointsNum));
  }
}

void Game::changeTower() {
  if ((int)time.asSeconds() == 60) {
    towerTex.loadFromFile("src/Textures/stoneTower2.png");
    tower.setTexture(towerTex);
    for (int i = 0; i < NUM; i++) {
      platform[i].platTex.loadFromFile("src/Textures/platform2v.png");
      platform[i].platSprite.setTexture(platform[i].platTex);
    }
  }
  if ((int)time.asSeconds() == 120) {
    towerTex.loadFromFile("src/Textures/diamondTower.png");
    tower.setTexture(towerTex);
    for (int i = 0; i < NUM; i++) {
      platform[i].platTex.loadFromFile("src/Textures/platform1.png");
      platform[i].platSprite.setTexture(platform[i].platTex);
    }
  }
}

void Game::deathUpdate() {
  pollEvents();
  window->draw(over);
  window->draw(press);
  window->display();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    menuRunning = true;
}

void Game::menuRender() {
  window->clear();
  window->draw(menu);
  window->display();
}

void Game::render() {
  window->clear();
  window->draw(bg);
  window->draw(tower);
  window->draw(interface);
  window->draw(best);
  window->draw(points);
  window->draw(timeText);
  for (int i = 0; i < NUM; i++)
    platform[i].render(window);
  player.render(window);
  window->display();
}
