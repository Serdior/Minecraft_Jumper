#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>    
#include<cmath>    

class Player
{
private:

    bool canJump = true;
    sf::Texture tex;
    void updateMove();
    void jump();

public:
   Player();
   virtual ~Player(); 

   float gravity = 12.0f;
   sf::Vector2f vel = sf::Vector2f(0.0,0.0);
   sf::FloatRect playerBounds;
   sf::Sprite sprite;
   
   bool onGround = false;
   bool jumping = false;
   bool isStart = true;
   bool dead = false;

   void updateWindowCollision(sf::RenderTarget* target);
   void update(sf::RenderTarget* target);
   void render(sf::RenderTarget* target);
};
#endif