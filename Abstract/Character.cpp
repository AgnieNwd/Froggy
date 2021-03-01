//
// Created by dy on 19/02/2020.
//

#include "Character.hh"

Character::Character(){
    //constructeur
}

Character::~Character() {
    //Destucteur
}

int Character::GetLife() const {
    return this->life;
}

void Character::SetLife(int _life) {
    this->life = _life;

    std::list <IObserver*> :: iterator it;
    for (it = _listObserver.begin(); it != _listObserver.end(); ++it) {
        (*it)->Notify(this);
    }
}

double Character::GetWidth() const {
    return this->width;
}

void Character::SetWidth(double _width) {
    this->width = _width;
}

double Character::GetHeight() const {
    return this->height;
}

void Character::SetHeight(double _height) {
    this->height = _height;
}

int Character::GetLength() const {
    return this->length;
}

void Character::SetLength(int _length) {
    this->length = _length;
}

double Character::GetVitesse() const {
    return this->vitesse;
}

void Character::SetVitesse(double _vitesse) {
    this->vitesse = _vitesse;
}

std::string Character::GetDirection() const {
    return this->direction;
}

void Character::SetDirection(std::string _direction) {
    this->direction = _direction;
}

void Character::Move(std::string _direction, int _l) {
    if(_direction == "ok")
        _l = 0;
}

void Character::Draw(sf::RenderWindow* window) {

}

void Character::Update() {

}

std::string Character::GetName() {
    return this->name;
}

void Character::SetName(std::string _name) {
    this->name = _name;
}

TextureRessources* Character::GetRessource() {
    return ressource;
}
void Character::SetRessource(TextureRessources* _ressource) {
    this->ressource = _ressource;
}

double Character::GetLimitMap() const {
    return this->limitMap;
}

void Character::SetLimitMap(double _lm) {
    this->limitMap = _lm;
}

void Character::AddObserver(IObserver *ob) {
    _listObserver.push_back(ob);
}

void Character::RemoveObserver(IObserver *ob) {
    _listObserver.remove(ob);
}

std::string Character::Serialize() {
    nlohmann::json j;

    j["class"] = "Character";
    j["Y"] = this->GetHeight();
    j["X"] = this->GetWidth();
    j["Life"] = this->GetLife();
    return j.dump();
}



