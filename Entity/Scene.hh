//
// Created by dy on 19/02/2020.
//

#ifndef FROGGER_SCENE_HH
#define FROGGER_SCENE_HH

#include <list>
#include <string>
#include "../Abstract/AbstractEntity.hh"
#include "../Interface/ISerializable.hh"
#include "../Assets/Json/json.hpp"

class Scene: public ISerializable {
public:
    Scene();
    Scene(const std::string&);
    ~Scene();
    void AddEntity(AbstractEntity*);
    void RemoveEntity(AbstractEntity*);
    void Update(sf::RenderWindow*);
    virtual std::string Serialize() override;
    std::list<AbstractEntity*> GetEntities() const;
    void SetPause(bool);
    bool GetPause() const;

private:
    bool pause;
    std::list<AbstractEntity*> list;


};

#endif //FROGGER_SCENE_HH
