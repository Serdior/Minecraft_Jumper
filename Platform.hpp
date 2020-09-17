#ifndef PLATFORM_H
#define PLATFORM_H

#include<iostream>
#include<cstdlib>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include"Player.hpp"

#define PlatVel 0.7

class Platform
{
private:
    sf::Clock clock;
    sf::Time currTime;
    sf::Time prevTime;
    float accel = 0;
    float playerOut = 0;

public:
    Platform();
    virtual ~Platform();

    sf::Texture platTex;

    sf::FloatRect platBound;
    sf::Sprite platSprite;
    float vel = 0.f;

    void initPlatform(int i);
    void reinitPlatform();
    void update(Player* player, sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};
#endif