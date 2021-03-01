#ifndef Frog_hh
#define Frog_hh

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>
#include "../Abstract/Character.hh"
#include "../SFML/Animation.hpp"

class Frog : public Character {
private:
    Animation* animation;

public:
    Frog();
    std::string last;

    virtual void Update() override;
    virtual void Draw(sf::RenderWindow *) override;

    virtual std::string Serialize() override;

    void Move(std::string, int) override;
    void Fmove(int row, float deltaTime);

    ~Frog();
};

#endif /* Frog_hh */