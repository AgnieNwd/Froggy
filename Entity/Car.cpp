#include "Car.hh"

Car::Car () {
    this->SetLife(1);
    this->SetRessource(new TextureRessources("Assets/img/Texture_car.png"));
}

Car::~Car() {
   //destructeur 
}

void Car::Update() {
    TimeManager &TM = TimeManager::GetInstance();
    double second = TM.GetElapsedTime() / 1000.;

    if(this->GetDirection() == "Ouest") {
        this->SetWidth(this->GetWidth() - (second * this->GetVitesse()));
        if(this->GetWidth() + this->GetLength() < 0){
            this->SetWidth(this->GetLimitMap() + this->GetLength());
        }
    } else {
        this->SetWidth(this->GetWidth() + (second * this->GetVitesse()));
        if(this->GetWidth() > this->GetLimitMap() ) {
            this->SetWidth(0 - this->GetLength());
        }
    }
}

std::string Car::Serialize(){
    nlohmann::json _j;
    _j["entity"] = "Car";
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

void Car::Move(std::string, int) {
    //TODO
}

void Car::Draw(sf::RenderWindow *window) {
    sf::RectangleShape car(sf::Vector2f(96* this->GetLength(), 96));

    // position
    car.setPosition( this->GetWidth() * 96, this->GetHeight() * 96 + 8);

    // couleur
    sf::Texture carType = this->GetRessource()->GetTexture();
    carType.setSmooth(true);
    car.setTexture(&carType);

    sf::Vector2u textureSize = this->GetRessource()->GetTextureSize();
    textureSize.x /= 2;
    textureSize.y /= 3;

    if (this->GetName() == "Bus") {
        car.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0, textureSize.x, textureSize.y));
    }
    else if (this->GetName() == "SuperCar") {
        car.setTextureRect(sf::IntRect(textureSize.x * 1 , textureSize.y * 2, textureSize.x, textureSize.y));
    }
    else if (this->GetName() == "Car") {
        car.setTextureRect(sf::IntRect(textureSize.x * 1 , textureSize.y * 0, textureSize.x, textureSize.y));
    }


    // taille du rectangle
    //  car.setSize(sf::Vector2f(96 * this->GetLength(), 96));

    window->draw(car);
}