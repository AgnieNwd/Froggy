#include "Frog.hh"


Frog::Frog() {
    this->SetLife(3);
    this->SetVitesse(5);
    this->SetName("Frog");

    sf::Vector2u _imageCount(6, 8);
    float _switchTime = 0.25f;
    this->SetRessource(new TextureRessources("Assets/img/Animation_frog.png"));
    sf::Texture playerFrog = this->GetRessource()->GetTexture();
    this->animation = new Animation(&playerFrog, _imageCount, _switchTime);
}

Frog::~Frog() {
    //destructeur
}

void Frog::Update() {

}

void Frog::Draw(sf::RenderWindow *window) {
    sf::RectangleShape player(sf::Vector2f(96, 96));
    player.setPosition(this->GetWidth() * 96, this->GetHeight() * 96);

    sf::Texture playerFrog = this->GetRessource()->GetTexture();
    playerFrog.setSmooth(true);
    player.setTexture(&playerFrog);

    sf::Vector2u textureSize = this->GetRessource()->GetTextureSize();
    textureSize.x /= 6;
    textureSize.y /= 8;
    player.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0, textureSize.x, textureSize.y));

    if (this->GetDirection() == "Est" ) {
        Fmove(2, TimeManager::GetInstance().GetElapsedTime() / 1000.);
        player.setTextureRect(animation->uvRect);
        if (this->GetDirection() == "Stop") {
//            std::cout << "YA UN MEC QUI VA LE CHANGER EN STOP NEGRO" << std::endl;
        } else {
            last = this->GetDirection();
        }

    }  else if (this->GetDirection() == "Ouest" ) {
        Fmove(3, TimeManager::GetInstance().GetElapsedTime() / 1000.);
        player.setTextureRect(animation->uvRect);
        if (this->GetDirection() == "Stop") {
//            std::cout << "YA UN MEC QUI VA LE CHANGER EN STOP NEGRO" << std::endl;
        }else {
            last = this->GetDirection();
        }
    }  else if (this->GetDirection() == "Sud") {
        Fmove(4, TimeManager::GetInstance().GetElapsedTime() / 1000.);
        player.setTextureRect(animation->uvRect);
        if (this->GetDirection() == "Stop") {
//            std::cout << "YA UN MEC QUI VA LE CHANGER EN STOP NEGRO" << std::endl;
        }else {
            last = this->GetDirection();
        }
    } else if (this->GetDirection() == "Nord") {
        Fmove(1, TimeManager::GetInstance().GetElapsedTime() / 1000.);
        player.setTextureRect(animation->uvRect);
        if (this->GetDirection() == "Stop") {
//            std::cout << "YA UN MEC QUI VA LE CHANGER EN STOP NEGRO" << std::endl;
        }else {
            last = this->GetDirection();
        }
    }

    if (this->GetDirection() == "Stop") {
        if (last == "Est") {
            Fmove(5, TimeManager::GetInstance().GetElapsedTime() / 1000.);
            player.setTextureRect(animation->uvRect);
        } else if (last == "Ouest") {
            Fmove(6, TimeManager::GetInstance().GetElapsedTime() / 1000.);
            player.setTextureRect(animation->uvRect);
        } else if (last == "Sud") {
            Fmove(7, TimeManager::GetInstance().GetElapsedTime() / 1000.);
            player.setTextureRect(animation->uvRect);
        } else if (last == "Nord") {
            Fmove(0, TimeManager::GetInstance().GetElapsedTime() / 1000.);
            player.setTextureRect(animation->uvRect);
        }
    }

    Fmove(0, TimeManager::GetInstance().GetElapsedTime() / 1000.);

    if (this->GetLife() != 0) {
        window->draw(player);
    }
}

std::string Frog::Serialize() {
    nlohmann::json _j;
    _j["entity"] = "Frog";
    _j["name"] = this->GetName();
    _j["x"] = this->GetWidth();
    _j["y"] = this->GetHeight();
    _j["life"] = this->GetLife();
    _j["vitesse"] = this->GetVitesse();
    _j["direction"] = this->GetDirection();
    _j["length"] = this->GetLength();
    std::string _s = _j.dump(4);
    return _s;
}

void Frog::Move(std::string, int row) {
}

void Frog::Fmove(int row, float deltaTime) {
    animation->currentImage.y = row;
    animation->totalTime += deltaTime;

    if(animation->totalTime >= animation->switchTime) {

        animation->totalTime -= animation->switchTime;
        animation->currentImage.x++;

        if (animation->currentImage.x >= animation->imageCount.x) {
            animation->currentImage.x = 0;
            this->SetDirection("Stop");
        }
    }

    animation->uvRect.left = animation->currentImage.x * animation->uvRect.width;
    animation->uvRect.top = animation->currentImage.y * animation->uvRect.height;
}

