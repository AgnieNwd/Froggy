//
// Created by dy on 19/02/2020.
//

#include "Scene.hh"
#include "../TimeManager/TimeManager.hh"
#include <string>
#include <iostream>
#include <sstream>
#include "../Factory/EntityFactory.hh"

Scene::Scene() {
    this->pause = false;
}

Scene::Scene(const std::string& object) {
    auto j_obj = nlohmann::json::parse(object);
    std::list<AbstractEntity*> EntityListToReturn;

    EntityFactory* entityFactory = new EntityFactory();

    std::map<int, std::string>::iterator itr;

    std::map<int, std::string> map = j_obj["map"];
    for (itr = map.begin(); itr != map.end(); ++itr) {
        AddEntity(entityFactory->Unserialize(itr->second));
    }
}


Scene::~Scene() {

}

std::list<AbstractEntity *> Scene::GetEntities() const {
    return this->list;
}

void Scene::AddEntity(AbstractEntity *ae) {
    this->list.push_back(ae);
}

void Scene::RemoveEntity(AbstractEntity *ae) {
    this->list.remove(ae);
}

void Scene::Update(sf::RenderWindow* window) {
    for (auto const& ae : this->GetEntities()) {
        if (this->pause == false)
            ae->Update();
        ae->Draw(window);
    }
}

std::string Scene::Serialize() {
    nlohmann::json j_list = nlohmann::json::object();

    std::list <AbstractEntity*>::iterator it;
    std::list<std::string> list;
    std::map<int, std::string> map;

    int nb = 0;
    for (it = this->list.begin(); it != this->list.end(); ++it) {
        map[nb] = (*it)->Serialize();
        nb++;
    }

    j_list["map"] = map;

    return j_list.dump();
}

bool Scene::GetPause() const {
    return this->pause;
}

void Scene::SetPause(bool val) {
        this->pause = val;
}