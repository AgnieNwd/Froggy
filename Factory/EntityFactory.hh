#ifndef EntityFactory_hh
#define EntityFactory_hh

#include <iostream>
#include <stdio.h>

#include "../TimeManager/TimeManager.hh"
#include "../Entity/Frog.hh"
#include "../Entity/Log.hh"
#include "../Entity/Car.hh"
#include "../Entity/Snake.hh"
#include "../Entity/Fly.hh"

class EntityFactory {
private:

public:
    EntityFactory();
    ~EntityFactory();
    Character* Create(const std::string&);
    Character* Unserialize(const std::string&);
};
#endif /* EntityFactory_hpp */