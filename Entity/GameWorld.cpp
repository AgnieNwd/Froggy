//
// Created by dy on 22/02/2020.
//

#include "GameWorld.hh"
#include <time.h>

GameWorld::GameWorld() {
    this->level = 1;
    this->score = 0;
    this->scene = new Scene();
    this->timer = 60000; // ms
    this->nenuLeft = 4;
    this->enterMenu = true;

    this->StartRessources();
}

GameWorld::GameWorld(int _level, double _score) {
    this->level = _level;
    this->score = _score;
    this->scene = new Scene();
    this->timer = 60000; // ms
    this->nenuLeft = 4;
    this->enterMenu = true;

    this->StartRessources();
}


GameWorld::~GameWorld() {
    for (unsigned int i = 0; i < 2; ++i)
    {
        delete m_textures[i];
    }
}

void GameWorld::StartRessources() {
    // Path of our ressources
    std::string resourcePaths[3] =
    {
        "Assets/Fonts/ARCADECLASSIC.ttf", // Font path
        "Assets/img/heart.png", // Heart img file path
        "Assets/img/blur.png" // Blur img file path
    };

    // Load our Font
    if (!this->m_font.loadFromFile(resourcePaths[0]))
    {
        std::cerr << "[!] Cannot load ressource: '"+ resourcePaths[0]+ "' Exiting...\n";
        std::cin.get();
        exit(1);
    }

    // Load all other img texture. (i = 1) because we do not include the Font
    for (unsigned int i = 1; i < 3; ++i)
    {
        m_textures.push_back(new TextureRessources(resourcePaths[i]));
    }

    // Launch our Música
    if (!this->m_music.openFromFile("Assets/Music/Zelda.ogg"))
    {
        std::cerr << "[!] Cannot load ressource: 'Assets/Music/Zelda.ogg' Exiting...\n";
        std::cin.get();
        exit(1);
    }
    this->m_music.setVolume(20);
    this->m_music.play();
    this->m_music.setLoop(true);

    // sound_jump
    if (!this->jump_sound.openFromFile("Assets/Music/sound_jump.ogg"))
    {
        std::cerr << "[!] Cannot load ressource: 'Assets/Music/sound_jump.ogg' Exiting...\n";
        std::cin.get();
        exit(1);
    }

    this->jump_sound.setVolume(20);

    // Death_water
    if (!this->Death_water.openFromFile("Assets/Music/splash.ogg"))
    {
        std::cerr << "[!] Cannot load ressource: 'Assets/Music/splash.ogg' Exiting...\n";
        std::cin.get();
        exit(1);
    }
    this->Death_water.setVolume(50);

    // Death_car
    if (!this->Death_car.openFromFile("Assets/Music/punch.ogg"))
    {
        std::cerr << "[!] Cannot load ressource: 'Assets/Music/punch.ogg' Exiting...\n";
        std::cin.get();
        exit(1);
    }
    this->Death_car.setVolume(10);
}

void GameWorld::StartGame() {
    std::cout << "ok | Start Time manager" << std::endl;
    // Start our timer
    TimeManager::GetInstance().Start();


    srand (time(NULL));
    // Init our map & entities
    this->ConfigMap();
    this->InitLog();
    this->InitFrog();
    this->InitCar();
    this->InitSnake();
    this->InitFly();

    // Draw in console our map
    this->GetMap()->DrawConsole();

    // Exec the fucking loop game
    this->LoopGame();
}


void GameWorld::LoopGame() {
    int width = this->GetMap()->GetSizeWidth();
    int height = this->GetMap()->GetSizeHeight();

    Menu *menu = new Menu();

    // Create window with the same map's size
    sf::RenderWindow window(sf::VideoMode(width * BLOCK_SIZE,height * BLOCK_SIZE + BLOCK_SIZE, 128),"Froggyyyyy");

    while (window.isOpen() ) {//|| gameWorld->GetMap()->GetFrog()->GetLife() != 0) {
        // Limits framerate to 60FPS
        window.setFramerateLimit(60);

        this->Update(&window);

        // handle events
        this->EventsHandler(&window);

        // Draw
        window.clear();
        this->Draw(&window);

        // Launching menu
        if (enterMenu) {
            int commander = menu->LaunchMenu(&window);
            if (commander == -1) {
                window.close();
                return;
            }
            if (commander == 1)
                enterMenu = false;
        }

        window.display();
    }
}

void GameWorld::EventsHandler(sf::RenderWindow *window) {
    sf::Event event;
    while (window->pollEvent(event) && !enterMenu) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            this->GetScene()->SetPause(!this->GetScene()->GetPause());
        }
        if (this->GetMap()->GetFrog()->GetLife() != 0 && !this->GetScene()->GetPause()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (this->GetMap()->GetFrog()->GetWidth() < this->GetMap()->GetSizeWidth() - 1) { // check right map limit
                    this->GetMap()->GetFrog()->SetWidth(this->GetMap()->GetFrog()->GetWidth() + 1);
                    this->GetMap()->GetFrog()->SetDirection("Est");
                    this->jump_sound.setPlayingOffset(sf::seconds(0.f));
                    this->jump_sound.play();
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (this->GetMap()->GetFrog()->GetWidth() > 0 ) { // check left map limit
                    this->GetMap()->GetFrog()->SetWidth(this->GetMap()->GetFrog()->GetWidth() - 1);
                    this->GetMap()->GetFrog()->SetDirection("Ouest");
                    this->jump_sound.setPlayingOffset(sf::seconds(0.f));
                    this->jump_sound.play();
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (this->GetMap()->GetFrog()->GetHeight() > 0 ) {  // check up map limit
                    this->GetMap()->GetFrog()->SetHeight(this->GetMap()->GetFrog()->GetHeight() - 1);
                    this->GetMap()->GetFrog()->SetDirection("Nord");
                    this->jump_sound.setPlayingOffset(sf::seconds(0.f));
                    this->jump_sound.play();
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (this->GetMap()->GetFrog()->GetHeight() < this->GetMap()->GetSizeHeight() - 1) {  // check down map limit
                    this->GetMap()->GetFrog()->SetHeight(this->GetMap()->GetFrog()->GetHeight() + 1);
                    this->GetMap()->GetFrog()->SetDirection("Sud");
                    this->jump_sound.setPlayingOffset(sf::seconds(0.f));
                    this->jump_sound.play();
                }
            }

        }

    }
}


void GameWorld::Update(sf::RenderWindow* window) {
    // Update our timer
    TimeManager::GetInstance().Update();

    // Start countdown
    if (!this->GetScene()->GetPause() && !enterMenu)
        this->SetTimer(this->GetTimer() - TimeManager::GetInstance().GetElapsedTime());

    //handle timer Fly
    double FlyTimer = TimeManager::GetInstance().GetElapsedTime() / 1000.;
    totalTimerFly += FlyTimer;

    //reset Fly  ----------> Reset timer for the fly  : 5 seconds
    if (totalTimerFly > 5 || this->map->GetPostionMap(0,this->map->GetFly()->GetWidth()) == 5) {
        this->map->GetFly()->SetLife(0);
        this->InitFly();
        totalTimerFly = 0;
    }

    // Check all collisions
    Character *frog = this->GetMap()->GetFrog();
    this->CheckCollisionCar(frog);
    this->CheckCollisionLog(frog);
    this->CheckCollisionWall(frog);
    this->CheckCollisionArrival(frog);
    this->CheckCollisionSnake(frog);

    this->Endgame(window);
}

void GameWorld::Draw(sf::RenderWindow *window) {
    // Draw our map
    this->GetMap()->Draw(window);

    // Draw our entites
    this->GetScene()->Update(window);

    // Draw text for fps, level, score & timer
    this->GetFps(window);
    this->DrawText(window, this->GetMap()->GetSizeWidth() * BLOCK_SIZE - 200, this->GetMap()->GetSizeHeight() * BLOCK_SIZE + 5, "Level " + std::to_string(this->GetLevel()), 32, sf::Color::Green);
    this->DrawText(window, this->GetMap()->GetSizeWidth() * BLOCK_SIZE - 202, this->GetMap()->GetSizeHeight() * BLOCK_SIZE + 40, "Score  " + std::to_string((int)this->GetScore()), 32, sf::Color::Green);
    this->DrawText(window,  this->GetMap()->GetSizeWidth() * BLOCK_SIZE / 2 - 32, this->GetMap()->GetSizeHeight() * BLOCK_SIZE, std::to_string((int)this->GetTimer() / 1000), 64, sf::Color::Red);

    // Draw hearts for life
    for (unsigned int i = 0; i < this->GetMap()->GetFrog()->GetLife(); ++i) {
        this->DrawImg(window, 54 * i + 10, 10, 0.12, 0.12, this->GetTextureRessource()[0]->GetTexture());
    }

    // Pause
    if (this->GetScene()->GetPause()) {
        this->DrawImg(window, 0, 0, 1, 1, this->GetTextureRessource()[1]->GetTexture());
        this->DrawText(window,  this->GetMap()->GetSizeWidth() * BLOCK_SIZE / 2 - 300, 40, "Pause", 256, sf::Color::Green);
    }

}


double GameWorld::GetScore() const {
    return this->score;
}

void GameWorld::SetScore(double _score) {
    this->score = _score;
}

int GameWorld::GetLevel() const {
    return this->level;
}

void GameWorld::SetLevel(int _level) {
    this->level = _level;
}

double GameWorld::GetTimer() const {
    return this->timer;
}

void GameWorld::SetTimer(double _timer) {
    this->timer = _timer;
}

void GameWorld::ResetTimer() {
    this->SetTimer(60000);
}

int GameWorld::GetNenuLeft() const {
    return this->nenuLeft;
}

void GameWorld::SetNenuLeft(int _nenu) {
    this->nenuLeft = _nenu;
}

Map* GameWorld::GetMap() const {
    return this->map;
}

void GameWorld::SetMap(Map *_map) {
    this->map = _map;
}

Scene* GameWorld::GetScene() const {
    return this->scene;
}
void GameWorld::SetScene(Scene *_scene) {
    this->scene = _scene;
}

std::vector<TextureRessources *> GameWorld::GetTextureRessource() {
    return m_textures;
}

void GameWorld::ConfigMap() {
    switch(this->level){
        case 1:
            this->map = new Map(9, 25);
            break;
        case 2:
            this->map = new Map(11, 25);
            break;
        case 3:
            this->map = new Map(13, 25);
            break;
        case 4:
            this->map = new Map(15, 25);
            break;
    }
    this->map->InitMap();
}

void GameWorld::InitFrog() {
    EntityFactory *ef = new EntityFactory();

    // Init our Frog
    Character *frog = ef->Create("Frog");
    frog->SetHeight(this->map->GetSizeHeight() - 1);
    frog->SetWidth(this->map->GetSizeWidth() / 2);
    this->scene->AddEntity(frog);
    this->map->SetFrog(frog);

}

void GameWorld::InitSnake() {
    EntityFactory *ef = new EntityFactory();

    //init snake
    Character *snake = ef->Create("Snake");
    snake->SetHeight(this->map->GetSizeHeight()/2);
    snake->SetLimitMap(this->map->GetSizeWidth());
    snake->SetWidth(0);
    this->scene->AddEntity(snake);
    this->map->SetSnake(snake);
}

void GameWorld::InitFly() {
    nb = 0;
    // Randomize the position of the fly on the waterlily
    nb = rand() % 4 + 1;

    switch (nb) {
        case 1: {
            if (this->map->GetPostionMap(0,5) == 4)
                this->GenerateFly(5);
            break;
        }
        case 2: {
            if (this->map->GetPostionMap(0,10) == 4)
                this->GenerateFly(10);
            break;
        }
        case 3: {
            if (this->map->GetPostionMap(0,15) == 4)
                this->GenerateFly(15);
            break;
        }
        case 4: {
            if (this->map->GetPostionMap(0,20) == 4)
                this->GenerateFly(20);
            break;
        }
    }
}

void GameWorld::GenerateFly(int x) {
    EntityFactory *ef = new EntityFactory();

    //Init our Fly
    Character *fly = ef->Create("Fly");
    fly->SetHeight(0);
    fly->SetWidth(x);
    fly->SetLimitMap(this->map->GetSizeWidth());
    this->scene->AddEntity(fly);
    this->map->SetFly(fly);
}

void GameWorld::InitCar() {
    std::vector<int> height_routes = this->map->GetHeightRoutes(); // Get y location of cars

    // Init our cars
    for (int y = 0; y < height_routes.size(); y++) {
        int nb = rand() % 3 + 1;
        switch(nb) {
            case 1: {
                int i = 0;
                while (i != 4) {
                    this->GenerateEntities("Car", "Bus", 2, i * (- i^4) - y, this->map->GetSizeWidth(), height_routes[y], 3, "Est");
                    i++;
                }
                break;
            }
            case 2: {
                int i = 0;
                while (i != 4 ) {
                    this->GenerateEntities("Car", "Car", 5, i * (-i^4) - y, this->map->GetSizeWidth() , height_routes[y], 2, "Est");
                    i++;
                }

                break;
            }
            case 3: {
                int i = 0;
                while (i != 3 ) {
                    this->GenerateEntities("Car", "SuperCar", 10, this->map->GetSizeWidth() + (i * (i^4)) + y,this->map->GetSizeWidth(), height_routes[y], 2, "Ouest");
                    i++;
                }
                break;
            }
        }
    }
}
void GameWorld::InitLog() {
    std::vector<int> height_rivierre = this->map->GetHeightRivierre(); // Get y location of logs

    // Init our logs
    for (int y = 0; y < height_rivierre.size(); y++) {
        int nb = rand() % 3 + 1;
        switch(nb) {
            case 1: {
                int i = 0;
                while (i != 4){
                    this->GenerateEntities("Log", "ShortLog", 2, i * (-i ^4) - y, this->map->GetSizeWidth(), height_rivierre[y], 3, "Est");
                    i++;
                }
                break;
            }
            case 2: {
                int i = 0;
                while (i != 4 ) {
                    this->GenerateEntities("Log", "SmallLog", 4, i * (-i^4) - y, this->map->GetSizeWidth() , height_rivierre[y], 2, "Est");
                    i++;
                }

                break;
            }
            case 3: {
                int i = 0;
                while (i != 3) {
                    this->GenerateEntities("Log", "LongLog", 6, this->map->GetSizeWidth() + (i * (i^9)) + y,this->map->GetSizeWidth(), height_rivierre[y], 4, "Ouest");
                    i++;
                }
                break;
            }
        }
    }
}

void GameWorld::GenerateEntities(std::string type, std::string name, int speed, double width, double limitMap, double height, int taille, std::string direction) {
    EntityFactory *ef = new EntityFactory();
    Character *charact = ef->Create(type);
    charact->SetName(name);
    charact->SetVitesse(speed);
    charact->SetWidth(width);
    charact->SetLimitMap(limitMap);
    charact->SetHeight(height);
    charact->SetLength(taille);
    charact->SetDirection(direction);
    this->scene->AddEntity(charact);
    if (type == "Log")
        this->GetMap()->AddLog(charact);
    else
        this->GetMap()->AddCar(charact);
}


void GameWorld::DrawText(sf::RenderWindow *window, int posX, int posY, std::string _str, int _size, sf::Color color) {
    sf::Text text(_str, m_font, _size);
    text.setPosition(posX, posY);
    text.setFillColor(color);
    window->draw(text);
}


void GameWorld::GetFps(sf::RenderWindow *window) {
    double timeInSecond = TimeManager::GetInstance().GetElapsedTime() / 1000.;
    int fps = (int)(1.0f / timeInSecond);
    std::string fpsToString = "FPS  " + std::to_string(fps);
    this->DrawText(window, 0, this->GetMap()->GetSizeHeight() * 96 + 21, fpsToString, 32, sf::Color::White);
}

void GameWorld::DrawImg(sf::RenderWindow *window, int posX, int posY, double scaleX, double scaleY, sf::Texture texture) {
    sf::Sprite img;
    sf::Texture imgTexture = texture;
    // texture
    img.setTexture(imgTexture);
    // position
    img.setPosition(posX, posY);
    // scale image
    img.setScale(scaleX, scaleY);
    imgTexture.setSmooth(true);
    window->draw(img);
}

void GameWorld::CheckCollisionCar(Character * frog) {
    // Frog hit the car
    for(auto& car : this->GetMap()->GetCars()) {
        if (((frog->GetWidth() >= (int)car->GetWidth() && frog->GetWidth() <= ((int)car->GetWidth() + car->GetLength() ) )&& frog->GetHeight() == car->GetHeight()) && frog->GetLife() > 0) {
            frog->SetLife(frog->GetLife() - 1);
            this->Death_car.setPlayingOffset(sf::seconds(0.f));
            this->Death_car.play();
            frog->SetWidth(this->GetMap()->GetSizeWidth()/2);
            frog->SetHeight(this->GetMap()->GetSizeHeight() - 1);
        }
    }
}

void GameWorld::CheckCollisionLog(Character * frog) {
    // Frog jump on log
    double second = TimeManager::GetInstance().GetElapsedTime() / 1000.;

    bool isOnLog = false;
    for (auto& log : this->GetMap()->GetLogs()) {
        // Check if frog is on the same y position than the river
        if (frog->GetHeight() >= this->map->GetHeightRivierre()[0] && frog->GetHeight() <= this->map->GetHeightRivierre()[this->map->GetHeightRivierre().size() - 1]) {
            // 0.5 px margin added on both sides to avoid the frog from falling into the water if it is on extremities of log
            if (((frog->GetWidth() >= ((int)log->GetWidth() - 0.5) && frog->GetWidth() <= ((int)log->GetWidth() + (log->GetLength() + 0.5))) && frog->GetHeight() == log->GetHeight()) && frog->GetLife() > 0) {
                if ((int)frog->GetWidth() != this->map->GetSizeWidth() && (int)frog->GetWidth() >= 0 ) {
                    if (log->GetDirection() == "Ouest") {
                        frog->SetWidth(frog->GetWidth() - (second * log->GetVitesse()));
                    } else {
                        frog->SetWidth(frog->GetWidth() + (second * log->GetVitesse()));
                    }
                    frog->SetHeight(log->GetHeight());
                } else {
                    frog->SetLife(frog->GetLife() - 1);
                    frog->SetWidth(this->GetMap()->GetSizeWidth()/2);
                    frog->SetHeight(this->GetMap()->GetSizeHeight() - 1);
                }
                isOnLog = true;
            }
        }
    }

    // If frog is not on the same y position than the river then we convert his position to int
    std::vector<int> height_rivierre = this->map->GetHeightRivierre();
    if (frog->GetHeight() < height_rivierre[0] || frog->GetHeight() > height_rivierre[height_rivierre.size() - 1]) {
        frog->SetWidth((int)frog->GetWidth());
    }
    // Else if frog fall in water
    else if (!isOnLog) {
        frog->SetLife(frog->GetLife() - 1);
        this->Death_water.setPlayingOffset(sf::seconds(0.f));
        this->Death_water.play();
        frog->SetWidth(this->GetMap()->GetSizeWidth()/2);
        frog->SetHeight(this->GetMap()->GetSizeHeight() - 1);
    }
}

void GameWorld::CheckCollisionWall(Character* frog) {
    // Frog jump on a tree or on a nenu with a standing frog (aka the wall of dead)
    if (this->map->GetMap()[(int)frog->GetHeight()][(int)frog->GetWidth()] == 3 || this->map->GetMap()[(int)frog->GetHeight()][(int)frog->GetWidth()] == 5){
        frog->SetLife(frog->GetLife() - 1);
        frog->SetWidth(this->GetMap()->GetSizeWidth()/2);
        frog->SetHeight(this->GetMap()->GetSizeHeight() - 1);
    }
}

void GameWorld::CheckCollisionArrival(Character* frog) {
    // Frog jump on the nenuphar (a.k.a the arrival)
    if (this->map->GetMap()[(int) frog->GetHeight()][(int) frog->GetWidth()] == 4) {
        this->CheckCollisionFly(frog);
        this->SetScore(this->GetScore() + 200);
        this->map->SetMapPostion((int) frog->GetHeight(), (int) frog->GetWidth(), 5);
        frog->SetWidth(this->GetMap()->GetSizeWidth() / 2);
        frog->SetHeight(this->GetMap()->GetSizeHeight() - 1);

        this->map->ReloadTilemap();
        this->SetNenuLeft(this->GetNenuLeft() - 1);
        this->ResetTimer();
    }
}

void GameWorld::CheckCollisionSnake(Character* frog) {
    // frog hit the snake
    Character* snake = this->map->GetSnake();
    if (((frog->GetWidth() >= (int)snake->GetWidth() && frog->GetWidth() <= ((int)snake->GetWidth() + snake->GetLength())) && frog->GetHeight() == snake->GetHeight()) && frog->GetLife() > 0) {
        frog->SetLife(frog->GetLife() - 1);
        frog->SetWidth(this->GetMap()->GetSizeWidth()/2);
        frog->SetHeight(this->GetMap()->GetSizeHeight() - 1);
    }
}

void GameWorld::CheckCollisionFly(Character * frog) {
    // frog jump on the waterlily and gain puntos
    Character* fly = this->map->GetFly();
    if (((frog->GetWidth() >= (int)fly->GetWidth() && frog->GetWidth() <= ((int)fly->GetWidth() + fly->GetLength())) && frog->GetHeight() == fly->GetHeight()) && frog->GetLife() > 0) {
        this->SetScore(this->GetScore() + 500);
        this->map->GetFly()->SetLife(0);
        this->InitFly();
    }
}

void GameWorld::Endgame(sf::RenderWindow* window) {
    // Lose handle
    if ((this->GetNenuLeft() > 0 && this->GetTimer() < 0) || this->GetMap()->GetFrog()->GetLife() == 0) {
        Menu* menu = new Menu();
        m_music.stop();
        this->GetMap()->GetFrog()->SetLife(0);
        this->SetTimer(0);
        this->GetScene()->SetPause(true);
        menu->GameOverMenu(window);
    }
    // Win handle
    else if (this->GetNenuLeft() == 0 && this->GetTimer() > 0 && this->GetMap()->GetFrog()->GetLife() != 0) {
        Menu* menu = new Menu();
        m_music.stop();
        this->GetScene()->SetPause(true);
        menu->VictoryMenu(window, this->GetLevel(), this->GetScore());
    }
}