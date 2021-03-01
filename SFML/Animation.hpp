//
// Created by morgan.belin on 24/02/2020.
//

#ifndef MY_FROGGER_ANIMATION_HPP
#define MY_FROGGER_ANIMATION_HPP


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Animation {


public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();

    void Update(int row, float deltaTime );
    void UpdateMove(int row, float deltaTime);

public:
    sf::IntRect uvRect;

    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

};


#endif //MY_FROGGER_ANIMATION_HPP
