//
// Created by dy on 21/02/2020.
//

#include "Map.hh"


Map::Map(int x, int y) {
    this->SetSizeHeight(x);
    this->SetSizeWidth(y);
    std::vector<std::vector<int>> _map(x, std::vector<int>(y));
    this->map = _map;

    // load the tileset texture for map
    this->texture = new TextureRessources("Assets/img/tilemap.png");
}

Map::~Map() {
    delete texture;

    delete frog;

    for (auto& car : this->GetCars()) {
        this->RemoveCar(car);
        delete car;
    }

    for (auto& log : this->GetLogs()) {
        this->RemoveLog(log);
        delete log;
    }
}

std::vector<std::vector<int>> Map::GetMap() const {
    return this->map;
}

void Map::SetMapPostion(int y, int x, int data) {
    this->map[y][x] = data;

}
int Map::GetPostionMap(int y, int x) {
    return map[y][x];
}

int Map::GetSizeHeight() const {
    return this->sizeHeight;
}

void Map::SetSizeHeight(int _sizeHeight) {
    this->sizeHeight = _sizeHeight;
}

int Map::GetSizeWidth() const {
    return this->sizeWidth;
}

void Map::SetSizeWidth(int _sizeWidth) {
    this->sizeWidth = _sizeWidth;
}

void Map::AddCar(Character* car) {
    this->carList.push_back(car);
}

void Map::RemoveCar(Character* car) {
    this->carList.remove(car);
}

void Map::AddLog(Character* log) {
    this->logList.push_back(log);
}

void Map::RemoveLog(Character* log) {
    this->logList.remove(log);
}

/**
 *  0 = Grass aka sidewalk
 *  1 = Water
 *  2 = Road
 *  3 = Wall aka forest
 *  4 = Exit aka nenuphare
 */
void Map::InitMap() {
    for(int y = 0; y < this->sizeHeight; y++) {
        for (int x = 0; x < this->sizeWidth; x++) {
            if (y == 0 || y == this->sizeHeight - 1 || y == this->sizeHeight/2){
                if (y == 0) // place forest
                    this->SetMapPostion(y, x, 3);
                else // place sidewalk
                    this->SetMapPostion(y, x, 0);
                if (y == 0 && (x == 5 || x == 10 || x == 15 || x == 20)) // place nenuphare
                    this->SetMapPostion(y, x, 4);

            }
            else if (y > 0 && y < this->sizeHeight/2)  // place water
                this->SetMapPostion(y, x, 1);
            else // place road
                this->SetMapPostion(y, x, 2);
        }
    }

    // create the tilemap to draw it
    if (!ressource_map.load(this->texture->GetTexture(), sf::Vector2u(96, 96), this->GetMap(), this->GetSizeWidth(), this->GetSizeHeight()))
    {
        std::cerr << "[!] Cannot load tileset for map. Exiting...\n";
        std::cin.get();
        exit(1);
    }

}

void Map::ReloadTilemap() {
    if (!ressource_map.load(this->texture->GetTexture(), sf::Vector2u(96, 96), this->GetMap(), this->GetSizeWidth(), this->GetSizeHeight()))
    {
        std::cerr << "[!] Cannot load tileset for map. Exiting...\n";
        std::cin.get();
        exit(1);
    }
    this->DrawConsole();
}

void Map::DrawConsole() {
    for(int i = 0; i < this->sizeHeight; i++){
        for(int n = 0; n < this->sizeWidth; n++) {
            std::cout << this->GetPostionMap(i, n);
        }
        std::cout << std::endl;
    }
}

void Map::Draw(sf::RenderWindow *window) {
    window->draw(ressource_map);
}

Character *Map::GetFrog() const {
    return frog;
}

void Map::SetFrog(Character* _frog) {
    this->frog = _frog;
}

Character *Map::GetSnake() const {
    return snake;
}

void Map::SetSnake(Character* _snake) {
    this->snake = _snake;
}


Character *Map::GetFly() {
    return fly;
}

void Map::SetFly(Character *_fly) {
    this->fly = _fly;
}

std::vector<int> Map::GetHeightRoutes() {
    // Get all position y of our roads
    std::vector<int> y_position;
    for(int y = 0; y < this->sizeHeight; y++){
        if(this->map[y][0] == 2) {
            y_position.push_back(y);
        }
    }
    return y_position;
}

std::vector<int> Map::GetHeightRivierre() {
    // Get all position y of our rivier
    std::vector<int> position;
    for(int y = 0; y < this->sizeHeight; y++){
        if(this->map[y][0] == 1) {
            position.push_back(y);
        }
    }
    return position;
}

std::vector<int> Map::GetWidthWaterLily() {
    std::vector<int> position;
    for (int y = 0; y < this->sizeWidth; y++){
        if (this->map[0][y] == 4) {
            position.push_back(y);
        }
    }
    return position;
}

std::list<Character *> Map::GetCars() const {
    return this->carList;
}

std::list<Character *> Map::GetLogs() const {
    return this->logList;
}