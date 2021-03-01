//
// Created by dy on 05/03/2020.
//

#ifndef MY_FROGGER_SNAKE_HH
#define MY_FROGGER_SNAKE_HH

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>
#include "../Abstract/Character.hh"
#include "../SFML/Animation.hpp"

class Snake: public Character{
private:
Animation* animation;

public:
    Snake();
    std::string last;
    virtual void Update() override;
    virtual void Draw(sf::RenderWindow *) override;
    virtual std::string Serialize() override;
    void Move(std::string, int) override;
    void Smove(float deltaTime);

    ~Snake();
};


#endif //MY_FROGGER_SNAKE_HH
