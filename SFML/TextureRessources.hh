//
// Created by Agn on 26/02/2020.
//

#ifndef MY_FROGGER_TEXTURERESSOURCES_HH
#define MY_FROGGER_TEXTURERESSOURCES_HH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>


class TextureRessources {
public:
    TextureRessources(const std::string& path);
    ~TextureRessources();

    bool LoadFromFile(const std::string& path);

    sf::Texture GetTexture();
    sf::Vector2u GetTextureSize();

private:
    sf::Texture m_texture;
    sf::Vector2u textureSize;
};


#endif //MY_FROGGER_TEXTURERESSOURCES_HH
