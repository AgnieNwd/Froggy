//
// Created by dy on 19/02/2020.
//

#include "AbstractEntity.hh"

AbstractEntity::AbstractEntity() {

}

AbstractEntity::~AbstractEntity() {

}

void AbstractEntity::Draw(sf::RenderWindow*) {

}

void AbstractEntity::Update() {

}

std::string AbstractEntity::GetName() {
    return "no name";
}

std::string AbstractEntity::Serialize() {
    return "";
}

