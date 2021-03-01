//
// Created by dy on 19/02/2020.
//

#ifndef FROGGER_CHARACTER_HH
#define FROGGER_CHARACTER_HH

#include <stdio.h>
#include "AbstractEntity.hh"
#include "../Interface/IObservable.hh"
#include "../Interface/ISerializable.hh"
#include "../Assets/Json/json.hpp"
#include "../SFML/TextureRessources.hh"
//int BLOC_SIZE = 96;

class Character: public IObservable, public AbstractEntity {

protected:
    Character();

public:

    ~Character();

    int GetLife() const;
    void SetLife(int);

    double GetWidth() const;
    void SetWidth(double);

    double GetHeight() const;
    void SetHeight(double);

    int GetLength() const;
    void SetLength(int);

    double GetVitesse() const;
    void SetVitesse(double);

    virtual std::string GetName() override;
    void SetName(std::string);

    std::string GetDirection() const;
    void SetDirection(std::string);

    TextureRessources* GetRessource();
    void SetRessource(TextureRessources* _ressource);

    double GetLimitMap() const;
    void SetLimitMap(double);

    virtual void Move(std::string, int);

    virtual void Draw(sf::RenderWindow*) override;
    virtual void Update() override;

    virtual void AddObserver(IObserver*) override;
    virtual void RemoveObserver(IObserver*) override;

    virtual std::string Serialize() override;

private:
    int life;
    double width;
    double height;
    int length;
    double vitesse;
    std::string direction;
    std::string name;
    double limitMap;


    TextureRessources* ressource;

};


#endif //FROGGER_CHARACTER_HH
