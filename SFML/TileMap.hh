//
// Created by Agn on 24/02/2020.
//

#ifndef MY_FROGGER_TILEMAP_HH
#define MY_FROGGER_TILEMAP_HH


#include <SFML/Graphics.hpp>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable {
public:

    bool load(sf::Texture tileset, sf::Vector2u tileSize, std::vector<std::vector<int>> _map, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};


#endif //MY_FROGGER_TILEMAP_HH
