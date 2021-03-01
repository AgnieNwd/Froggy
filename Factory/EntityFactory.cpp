#include "EntityFactory.hh"

EntityFactory::EntityFactory() {
    //constructeur
}

EntityFactory::~EntityFactory() {
    //destructeur
}

Character* EntityFactory::Unserialize(const std::string& entity) {
    nlohmann::json j  = nlohmann::json::parse(entity);
    Character *cha;
    if (j.value("entity", "entity") == "Log") {
        cha = new Log();
        cha->SetName(j.value("name", "Log"));
        cha->SetWidth(j.value("x", 0));
        cha->SetHeight(j.value("y", 0));
        cha->SetLife(j.value("life", 0));
        cha->SetVitesse(j.value("vitesse", 0));
        cha->SetDirection(j.value("direction", "Ouest"));
        cha->SetLength(j.value("length", 0));
        return cha;
    }
    else if (j.value("entity", "entity") == "Car") {
        cha = new Car();
        cha->SetName(j.value("name", "Car"));
        cha->SetWidth(j.value("x", 0));
        cha->SetHeight(j.value("y", 0));
        cha->SetLife(j.value("life", 0));
        cha->SetVitesse(j.value("vitesse", 0));
        cha->SetDirection(j.value("direction", "Est"));
        cha->SetLength(j.value("length", 0));
        return cha;
    }
    else if (j.value("entity", "entity") == "Frog") {
        cha = new Frog();
        cha->SetName(j.value("name", "Frog"));
        cha->SetWidth(j.value("x", 0));
        cha->SetHeight(j.value("y", 0));
        cha->SetLife(j.value("life", 0));
        cha->SetVitesse(j.value("vitesse", 0));
        cha->SetDirection(j.value("direction", "Nord"));
        cha->SetLength(j.value("length", 0));
        return cha;
    }
    else if (j.value("entity", "entity") == "Snake") {
        cha = new Frog();
        cha->SetName(j.value("name", "Snake"));
        cha->SetWidth(j.value("x", 0));
        cha->SetHeight(j.value("y", 0));
        cha->SetLife(j.value("life", 0));
        cha->SetVitesse(j.value("vitesse", 0));
        cha->SetDirection(j.value("direction", "Est"));
        cha->SetLength(j.value("length", 0));
        return cha;
    }
    else if ( j.value("entity", "entity") == "FLy") {
        cha = new Fly();
        cha->SetName(j.value("name", "Fly"));
        cha->SetWidth(j.value("x", 0));
        cha->SetHeight(j.value("y", 0));
        cha->SetLife(j.value("life", 0));
        cha->SetVitesse(j.value("vitesse", 0));
        cha->SetDirection(j.value("direction", "gauche"));
        cha->SetLength(j.value("length", 0));
        return cha;
    }
    return cha = nullptr;
}

Character* EntityFactory::Create(const std::string& entity) {
    Character *cha;
    if (entity == "Log") {
        return cha = new Log();
    }
    else if (entity == "Car") {
        return cha = new Car();
    }
    else if (entity == "Frog") {
        return cha = new Frog();
    }
    else if (entity == "Snake") {
        return cha = new Snake();
    }
    else if (entity == "Fly") {
        return cha = new Fly();
    }
    else {
        return cha = NULL;
    }
}