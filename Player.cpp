#include "Player.hpp"

Player::Player() {
  tex.loadFromFile("src/Textures/steve.png");
  sprite.setTexture(tex);
  sprite.setPosition(sf::Vector2f(440.f, 700.f));
}

Player::~Player() {}

void Player::updateMove() {

  // vel.x = 0.0f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    vel.x = -12.0f;

  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    vel.x = 12.0f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
    jumping = true;
    isStart = false;
    onGround = false;
    vel.y = -35;
  }

  if (!onGround)
    vel.y += gravity * 0.15;
  if (vel.y >= 0)
    jumping = false;
  if (vel.x > 0)
    vel.x -= 4;
  if (vel.x < 0)
    vel.x += 4;

  sprite.move(vel.x, vel.y);
}

void Player::updateWindowCollision(sf::RenderTarget *target) {
  playerBounds = sprite.getGlobalBounds();
  if (playerBounds.top <= -playerBounds.height / 2) {
    sprite.setPosition(playerBounds.left, -playerBounds.height / 2);
    playerBounds = sprite.getGlobalBounds();
  }
  if (playerBounds.left <= 120.f) {
    sprite.setPosition(120.f, playerBounds.top);
    playerBounds = sprite.getGlobalBounds();
  }
  if (playerBounds.left + playerBounds.width >= 770.f) {
    sprite.setPosition(770.f - playerBounds.width, playerBounds.top);
    playerBounds = sprite.getGlobalBounds();
  }
  if (playerBounds.top + playerBounds.height > target->getSize().y && isStart) {
    sprite.setPosition(playerBounds.left,
                       target->getSize().y - playerBounds.height);
    playerBounds = sprite.getGlobalBounds();
  } else if (playerBounds.top + playerBounds.height > target->getSize().y) {
    sprite.setPosition(playerBounds.left,
                       target->getSize().y - playerBounds.height);
    dead = true;
  }
}

void Player::update(sf::RenderTarget *target) {
  updateWindowCollision(target);
  if (!dead)
    updateMove();
}

void Player::render(sf::RenderTarget *target) { target->draw(sprite); }