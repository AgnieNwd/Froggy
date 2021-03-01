//
// Created by dy on 19/02/2020.
//

#ifndef FROGGER_ABSTRACTENTITY_HH
#define FROGGER_ABSTRACTENTITY_HH


#include <stdio.h>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../TimeManager/TimeManager.hh"
#include "../Interface/ISerializable.hh"

class AbstractEntity : public ISerializable {
public:
    AbstractEntity();

    virtual void Draw(sf::RenderWindow*) = 0;
    virtual void Update() = 0;
    virtual std::string GetName();

    virtual ~AbstractEntity();

    virtual std::string Serialize() override;
};



#endif //FROGGER_ABSTRACTENTITY_HH
