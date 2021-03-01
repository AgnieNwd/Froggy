#ifndef MY_FROGGER_FLY_HH
#define MY_FROGGER_FLY_HH

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>
#include "../Abstract/Character.hh"
#include "../SFML/Animation.hpp"

class Fly : public Character, public IObserver {
public:
    Fly();
    ~Fly();
    void Update() override;
    void Draw(sf::RenderWindow *) override;

    std::string Serialize() override;

    void Move(std::string, int) override;

    void Notify(IObservable*) override;

    sf::Music m_bzzsound;
};


#endif //MY_FROGGER_FLY_HH
