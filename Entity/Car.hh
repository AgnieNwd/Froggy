#ifndef Car_hh
#define Car_hh

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>
#include "../Abstract/Character.hh"
#include "../TimeManager/TimeManager.hh"
#include "../SFML/Animation.hpp"

class Car : public Character {

public:
    Car();
    virtual void Update() override ;
    virtual void Draw(sf::RenderWindow *) override;
    virtual std::string Serialize() override;
    void Move(std::string, int) override;
    ~Car();
};

#endif /* Car_hh */