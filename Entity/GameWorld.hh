//
// Created by dy on 22/02/2020.
//

#ifndef MY_FROGGER_GAMEWORLD_HH
#define MY_FROGGER_GAMEWORLD_HH

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "../SFML/TextureRessources.hh"
#include "../SFML/Menu.hh"
#include "Map.hh"
#include "Scene.hh"


class GameWorld {
public: const int BLOCK_SIZE = 96;

public:
    GameWorld();
    GameWorld(int, double);
    ~GameWorld();

    void StartGame();
    void StartRessources();
    void LoopGame();
    void EventsHandler(sf::RenderWindow *window);
    void Draw(sf::RenderWindow *window);

    void Update(sf::RenderWindow *window);

    int GetLevel() const;
    void SetLevel(int);

    double GetTimer() const;
    void SetTimer(double);
    void ResetTimer();

    double GetScore() const;
    void SetScore(double);

    int GetNenuLeft() const;
    void SetNenuLeft(int);

    Map* GetMap() const;
    void SetMap(Map*);

    Scene* GetScene() const;
    void SetScene(Scene*);

    std::vector<TextureRessources*> GetTextureRessource();

    void ConfigMap();

    void InitFrog();
    void InitSnake();
    void InitCar();
    void InitLog();
    void InitFly();

    void CheckCollisionCar(Character*);
    void CheckCollisionLog(Character*);
    void CheckCollisionWall(Character*);
    void CheckCollisionArrival(Character*);
    void CheckCollisionSnake(Character*);
    void CheckCollisionFly(Character*);

    void GenerateEntities(std::string, std::string, int, double, double, double, int, std::string);
    void GenerateFly(int x);

    void DrawText(sf::RenderWindow *window, int, int, std::string, int, sf::Color);
    void DrawImg(sf::RenderWindow *window, int, int, double, double, sf::Texture);
    void GetFps(sf::RenderWindow *window);

    void Endgame(sf::RenderWindow *window);

private:
    bool enterMenu;

    int level;
    double timer;
    double score;
    int nenuLeft;
    float totalTimerFly;
    int nb ;

    Map* map;
    Scene* scene;

    sf::Font m_font;
    sf::Music m_music;
    sf::Music jump_sound;
    sf::Music Death_water;
    sf::Music Death_car;
    std::vector<TextureRessources*> m_textures; // [0]: heart img, [1]: blur img
};


#endif //MY_FROGGER_GAMEWORLD_HH
