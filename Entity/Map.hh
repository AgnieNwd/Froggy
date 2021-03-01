//
// Created by dy on 21/02/2020.
//

#ifndef MY_FROGGER_MAP_HH
#define MY_FROGGER_MAP_HH

#include <vector>
#include <list>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../SFML/TileMap.hh"

#include "Log.hh"
#include "Car.hh"

#include "../Abstract/Character.hh"
#include "../Factory/EntityFactory.hh"

class Map {

public:
    Map(int, int);
    ~Map();

    int GetSizeHeight() const;
    void SetSizeHeight(int);

    int GetSizeWidth() const;
    void SetSizeWidth(int);

    std::vector<std::vector<int>> GetMap() const;
    void SetMapPostion(int y, int x, int data);
    int GetPostionMap(int y, int x);

    void AddLog(Character*);
    void RemoveLog(Character*);
    std::list<Character*> GetLogs() const;

    void AddCar(Character*);
    void RemoveCar(Character*);
    std::list<Character*> GetCars() const;

    Character* GetFrog() const;
    void SetFrog(Character*);

    Character* GetSnake() const;
    void SetSnake(Character*);

    Character* GetFly();
    void SetFly(Character*);

    void InitMap();
    void DrawConsole();
    void Draw(sf::RenderWindow*);
    void ReloadTilemap();

    std::vector<int> GetHeightRoutes();
    std::vector<int> GetHeightRivierre();
    std::vector<int> GetWidthWaterLily();

private:
    int sizeHeight;
    int sizeWidth;
    std::vector<std::vector<int>> map;

    TextureRessources* texture;
    TileMap ressource_map;

    std::list<Character*> logList;
    std::list<Character*> carList;
    Character* frog;
    Character* snake;
    Character* fly;
};


#endif //MY_FROGGER_MAP_HH
