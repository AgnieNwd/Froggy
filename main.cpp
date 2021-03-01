//
// Created by dy on 20/02/2020.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Entity/GameWorld.hh"


/*
 *  MEMO ::
 *  Un bloc = 96 pixels
 *  Volume = 20
 */

int main() {

    GameWorld *gameWorld = new GameWorld();

    gameWorld->StartGame();

    return 0;

}