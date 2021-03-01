//
// Created by Agn on 03/03/2020.
//

#include "Menu.hh"

Menu::Menu() {
    // Path of our ressources
    std::string resourcePaths[5] =
    {
            "Assets/Fonts/FLUBBER_.TTF", // Font path
            "Assets/img/menu_win.png", // Win menu path
            "Assets/img/menu_dead.png", // Dead menu path
            "Assets/img/blur2.png", // blur menu path
            "Assets/img/Logo_Froggy.png", // Logo Froggy menu path
    };

    std::string texts[4] =
    {
            "Start game",
            "Quit",
            "Congratulation !\n Play Again ?",
            "Next Level :)"
    };

    // Load our Font
    if (!this->m_font.loadFromFile(resourcePaths[0]))
    {
        std::cerr << "[!] Cannot load ressource: '" + resourcePaths[0] + "' Exiting...\n";
        std::cin.get();
        exit(1);
    }

    // Load all other img texture. (i = 1) because we do not include the Font
    for (unsigned int i = 1; i < 5; ++i)
    {
        m_textures.push_back(new TextureRessources(resourcePaths[i]));
    }

    for (unsigned int i = 0; i < 4; ++i)
    {
        sf::Text text(texts[i], m_font);
        if (i == 0) // "Start game" init to blue
            text.setFillColor(sf::Color::Blue);
        if (i == 2 || i == 3) // "Play game" & "Next Level" init to cyan
            text.setFillColor(sf::Color::Cyan);
        m_texts.push_back(text);
    }
}

Menu::~Menu() {
    for (unsigned int i = 0; i < 4; ++i)
    {
        delete m_textures[i];
    }
}

int Menu::LaunchMenu(sf::RenderWindow* window) {
    sf::Texture blur = m_textures[2]->GetTexture(); // blur
    this->DrawImg(window, -250.0f, 0, blur);

    sf::Texture froggy = m_textures[3]->GetTexture(); // froggy
    this->DrawImg(window, 430.0f, 20, froggy);

    // "Start"
    m_texts[0].setPosition(900, 460);
    m_texts[0].setCharacterSize(132);

    // "Quit"
    m_texts[1].setPosition(1100, 650);
    m_texts[1].setCharacterSize(100);


    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window->close();
            return -1;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
            choice = 1;
            m_texts[0].setFillColor(sf::Color::Blue);
            m_texts[1].setFillColor(sf::Color::White);
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
            choice = -1;
            m_texts[0].setFillColor(sf::Color::White);
            m_texts[1].setFillColor(sf::Color::Blue);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            return choice ? choice : 1;
        }
    }


    window->draw(m_texts[0]);
    window->draw(m_texts[1]);

    return 0;
}

void Menu::VictoryMenu(sf::RenderWindow *windowGame, int _level, double _score)
{
    // "Play again ?"
    if (_level == 4) {
        m_texts[2].setPosition(350, 410);
        m_texts[2].setCharacterSize(128);
    } else { // "Next Level"
        m_texts[3].setPosition(350, 550);
        m_texts[3].setCharacterSize(128);
    }

    // "Quit"
    m_texts[1].setPosition(350, 750);
    m_texts[1].setCharacterSize(128);

    sf::Text score_text("Your score : " + std::to_string((int)_score), m_font, 128);
    score_text.setPosition(330, 100);
    score_text.setFillColor(sf::Color::Green);

    sf::Texture menu_win = m_textures[0]->GetTexture();

    while (windowGame->isOpen()) {
        windowGame->clear();

        sf::Event event;
        while (windowGame->pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                windowGame->close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                choice = 1;
                if (_level == 4)
                    m_texts[2].setFillColor(sf::Color::Cyan); // "play game"
                else
                    m_texts[3].setFillColor(sf::Color::Cyan); // "next level"

                m_texts[1].setFillColor(sf::Color::White);
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                choice = -1;
                if (_level == 4)
                    m_texts[2].setFillColor(sf::Color::White); // "play game"
                else
                    m_texts[3].setFillColor(sf::Color::White); // "next level"

                m_texts[1].setFillColor(sf::Color::Cyan);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                choice = choice ? choice : 1;
                if (choice == 1) {
                    windowGame->close();
                    if (_level == 4) {
                        GameWorld* GW = new GameWorld();
                        GW->StartGame();
                    } else {
                        int newlevel = _level + 1;
                        GameWorld *GW = new GameWorld(newlevel, _score);
                        GW->StartGame();
                    }
                } else if (choice == -1) {
                    windowGame->close();
                }
            }
        }

        this->DrawImg(windowGame, 0, 0, menu_win);

        if (_level == 4)
            windowGame->draw(m_texts[2]);
        else
            windowGame->draw(m_texts[3]);

        windowGame->draw(m_texts[1]);
        windowGame->draw(score_text);

        windowGame->display();
    }

}

void Menu::GameOverMenu(sf::RenderWindow *windowGame)
{
    windowGame->clear();
    sf::Texture menu_dead = m_textures[1]->GetTexture();

    sf::Text gameover_text("Game Over Looser!", m_font, 128);
    gameover_text.setPosition(350, 580);
    gameover_text.setFillColor(sf::Color::Red);

    sf::Text playagain_text("Enter to play again\nEscape to close", m_font, 64);
    playagain_text.setPosition(350, 750);

    this->DrawImg(windowGame, 0, 0, menu_dead);
    windowGame->draw(gameover_text);
    windowGame->draw(playagain_text);
    windowGame->display();
    while (windowGame->isOpen()) {
        sf::Event event;
        while (windowGame->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowGame->close();
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                windowGame->close();
                GameWorld* GW = new GameWorld();
                GW->StartGame();
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                windowGame->close();
            }
        }
    }
}

void Menu::Draw(sf::RenderWindow *window) {

}

void Menu::DrawImg(sf::RenderWindow *window, int posX, int posY, sf::Texture texture) {
    sf::Sprite img;
    sf::Texture imgTexture = texture;
    imgTexture.setSmooth(true);

    img.setPosition(posX, posY);
    img.setTexture(imgTexture);
    img.move(sf::Vector2f(250.0f, 0));
    window->draw(img);
}
