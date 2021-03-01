//
// Created by Agn on 03/03/2020.
//

#ifndef MY_FROGGER_MENU_HH
#define MY_FROGGER_MENU_HH

#include "SFML/Graphics.hpp"
#include "TextureRessources.hh"
#include "../Entity/GameWorld.hh"


class Menu {
public: int choice;
public:
    Menu();
    ~Menu();

    void Draw(sf::RenderWindow*);
    void DrawImg(sf::RenderWindow*, int, int, sf::Texture);

    int LaunchMenu(sf::RenderWindow*);
    void VictoryMenu(sf::RenderWindow*, int, double);
    void GameOverMenu(sf::RenderWindow*);

private:
//    GameWorld* m_gameWorld;
//    GameWorld* gameWorld;
    sf::Font m_font;

    std::vector<sf::Text> m_texts;
    std::vector<TextureRessources*> m_textures; // [0] : menu_win,  [1] : menu_dead,  [2] : rainbow_blur,  [3] : logo_froggy,
};


#endif //MY_FROGGER_MENU_HH
