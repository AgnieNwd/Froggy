#include "Fly.hh"

Fly::Fly() {
    this->SetLife(1);
    this->SetVitesse(1);
    this->SetName("Fly");
    this->SetLength(1);
    this->SetRessource(new TextureRessources("Assets/img/Fly_texture.png"));
    this->AddObserver(this);

    // sound_
    if (!this->m_bzzsound.openFromFile("Assets/Music/fly_by.ogg"))
    {
        std::cerr << "[!] Cannot load ressource: 'Assets/Music/fly_by.ogg' Exiting...\n";
        std::cin.get();
        exit(1);
    }
    this->m_bzzsound.setVolume(8);

    //constructeur
}

Fly::~Fly() {
    //Destructeur
    this->RemoveObserver(this);
}

void Fly::Update() {
    TimeManager &TM = TimeManager::GetInstance();
    this->SetWidth(this->GetWidth());
    this->SetHeight(this->GetHeight());
    if (this->GetLife() == 0)
        this->RemoveObserver(this);
}

void Fly::Draw(sf::RenderWindow * window) {
    sf::RectangleShape Fly(sf::Vector2f(96  * this->GetLength(), 96));

    // position
    Fly.setPosition( this->GetWidth() * 96, this->GetHeight() * 96);

    // texture
    sf::Texture FlyType = this->GetRessource()->GetTexture();
    FlyType.setSmooth(true);
    Fly.setTexture(&FlyType);

    sf::Vector2u textureSize = this->GetRessource()->GetTextureSize();
    textureSize.x /= 1;
    textureSize.y /= 1;

    Fly.setTextureRect(sf::IntRect(textureSize.x * 0 , textureSize.y * 0, textureSize.x, textureSize.y));
    if (this->GetLife() != 0) {
        window->draw(Fly);
    }
}

std::string Fly::Serialize() {
    nlohmann::json _j;
    _j["entity"] = "Fly";
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


void Fly::Move(std::string, int) {

}

void Fly::Notify(IObservable *) {
    std::cout << "RESPAWN" << std::endl;
    this->m_bzzsound.play();
}
