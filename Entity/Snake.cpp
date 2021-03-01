//
// Created by dy on 05/03/2020.
//

#include "Snake.hh"

Snake::Snake(){
    this->SetVitesse(5);
    this->SetName("Snake");
    this->SetDirection("Est");
    this->SetLength(3);

    this->SetRessource(new TextureRessources("Assets/img/snaky.png"));
    sf::Texture snaky = this->GetRessource()->GetTexture();
    sf::Vector2u _imageCount(4, 8);
    this->animation = new Animation(&snaky, _imageCount, 0.1f);

}

Snake::~Snake() {

}


void Snake::Update() {
    TimeManager &TM = TimeManager::GetInstance();
    double second = TM.GetElapsedTime() / 1000.;
    this->SetWidth(this->GetWidth() + (second * this->GetVitesse()));
    //using random to spawn snake
    int nb = rand() % 250 + 1;
    if (this->GetWidth() > (this->GetLimitMap() * nb)) {
        this->SetWidth(0 - this->GetLength());
    }
}

void Snake::Draw(sf::RenderWindow *window) {
    sf::RectangleShape snake(sf::Vector2f(96  * this->GetLength(), 96));

    // position
    snake.setPosition( this->GetWidth() * 96, this->GetHeight() * 96);

    // texture
   sf::Texture Snaky = this->GetRessource()->GetTexture();
    Snaky.setSmooth(true);
    snake.setTexture(&Snaky);

    sf::Vector2u textureSize = this->GetRessource()->GetTextureSize();
    textureSize.x /= 4;
    textureSize.y /= 8;

    snake.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0, textureSize.x, textureSize.y));


    //snake.setFillColor(sf::Color::White);
    snake.setTextureRect(animation->uvRect);
    Smove(TimeManager::GetInstance().GetElapsedTime() / 1000.);

    window->draw(snake);
}

std::string Snake::Serialize() {
    nlohmann::json _j;
    _j["entity"] = "Snake";
    _j["name"] = this->GetName();
    _j["x"] = this->GetWidth();
    _j["y"] = this->GetWidth();
    _j["life"] = this->GetLife();
    _j["vitesse"] = this->GetVitesse();
    _j["direction"] = this->GetDirection();
    _j["length"] = this->GetLength();
    std::string _s = _j.dump(4);
    return _s;
}

void Snake::Move(std::string, int) {
    // TODO
}

void Snake::Smove(float deltaTime) {
    animation->totalTime += deltaTime;

    if(animation->totalTime >= animation->switchTime) {

        animation->totalTime -= animation->switchTime;
        animation->currentImage.x++;

        if (animation->currentImage.x >= animation->imageCount.x) {
            animation->currentImage.x = 0;
            animation->currentImage.y++;
        }
        if(animation->currentImage.y >= animation->imageCount.y){
            animation->currentImage.y = 0;
        }

    }
    animation->uvRect.left = animation->currentImage.x * animation->uvRect.width;
    animation->uvRect.top = animation->currentImage.y * animation->uvRect.height;
}
