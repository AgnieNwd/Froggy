//
// Created by Agn on 26/02/2020.
//

#include "TextureRessources.hh"

TextureRessources::TextureRessources(const std::string &path) {

    if (!this->LoadFromFile(path))
    {
        std::cerr << "[!] Cannot load resource: '" << path << std::endl;
        std::cin.get();
        std::exit(1);
    }

    std::cout << "[ok] ressource loaded : " << path << std::endl;
}

TextureRessources::~TextureRessources() {

}

bool TextureRessources::LoadFromFile(const std::string &path)
{
    if (!m_texture.loadFromFile(path))
    {
        textureSize.x = 0;
        textureSize.y = 0;

        return false;
    }

    textureSize = m_texture.getSize();

    return true;
}

sf::Texture TextureRessources::GetTexture() {
    return m_texture;
}

sf::Vector2u TextureRessources::GetTextureSize() {
    return textureSize;
}


