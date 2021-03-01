#include "Log.hh"

Log::Log() {
    this->SetLife(1);
    this->SetVitesse(3);
    this->SetName("Log");
    this->SetRessource(new TextureRessources("Assets/img/Log.png"));
    //constructeur
}

Log::~Log() {
    //destructeur
}

void Log::Update() {
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

void Log::Draw(sf::RenderWindow *window) {
    sf::RectangleShape log(sf::Vector2f(96  * this->GetLength(), 96));

    // position
    log.setPosition( this->GetWidth() * 96, this->GetHeight() * 96);

    // texture
    sf::Texture LogType = this->GetRessource()->GetTexture();
    LogType.setSmooth(true);
    log.setTexture(&LogType);

    sf::Vector2u textureSize = this->GetRessource()->GetTextureSize();
    textureSize.x /= 1;
    textureSize.y /= 1;

    if (this->GetName() == "ShortLog") {
        log.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0, textureSize.x, textureSize.y));
    }
    else if (this->GetName() == "SmallLog") {
        log.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0, textureSize.x, textureSize.y));
    }
    else if (this->GetName() == "LongLog") {
        log.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0, textureSize.x, textureSize.y));
    }


    // taille du rectangle
    //log.setSize(sf::Vector2f(96 * this->GetLength(), 92));

    window->draw(log);
}

std::string Log::Serialize() {
    nlohmann::json _j;
    _j["entity"] = "Log";
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

void Log::Move(std::string, int) {
    // TODO
}
