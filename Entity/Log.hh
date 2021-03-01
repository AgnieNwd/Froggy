#ifndef Log_hh
#define Log_hh

#include <iostream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>
#include "../Abstract/Character.hh"
#include "../TimeManager/TimeManager.hh"

class Log : public Character {


public:
    Log();
    virtual void Update() override;
    virtual void Draw(sf::RenderWindow *) override;
    virtual std::string Serialize() override;
    void Move(std::string, int) override;
    ~Log();
};

#endif /* Log_hh */