#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->bgRect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->bgRect.setFillColor(sf::Color::Black);
    this->paused = false;
    this->initWorld();
    
    this->looserFont.loadFromFile("../util/PacfontGood.ttf");
    this->textFont.loadFromFile("../util/SF Atarian System.ttf");

    ghosts.push_back(new Ghost(sf::Vector2f(160, 60), blinky));
    ghosts.push_back(new Ghost(sf::Vector2f(740, 760), pinky));
    ghosts.push_back(new Ghost(sf::Vector2f(740, 60), inky));
    ghosts.push_back(new Ghost(sf::Vector2f(160, 760), clyde));
    this->endGameDialog();
    std::cout << "New Game State" << std::endl;
}

GameState::~GameState()
{
    this->endState(); 

    for (Ghost *ghost : this->ghosts)
        delete ghost;
    this->ghosts.clear();

    for (sf::Sprite* sprite : this->heartSprites)
        delete sprite;
    heartSprites.clear();

    delete this->map;
    delete this->scoreText;
    delete this->text;
    delete this->highScoreText;
    delete this->currentScoreText;
}

void GameState::initWorld()
{
    this->map = new Map();
    this->map->loadMapFromFile();
    this->map->initTiles();
    this->initStatusbar();
}

void GameState::initStatusbar()
{
    this->font.loadFromFile("../util/SF Atarian System.ttf");
    this->font.setSmooth(true);
    this->currentScoreText = new sf::Text(font, "score: 0", 20);
    this->currentScoreText->setPosition(sf::Vector2f(20, 850));

    this->heartTexture.loadFromFile("../util/heart.png");

    for (int i = 0; i < health; i++)
    {
        heartSprites.push_back(new sf::Sprite(this->heartTexture));
        heartSprites[i]->setScale(sf::Vector2f(0.1, 0.1));
        heartSprites[i]->setPosition(sf::Vector2f(600 + i * 20, 850));
    }
}

void GameState::endState()
{
    std::cout << "Ending Game State" << std::endl;
}

void GameState::updateInput(const float& dt, sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
        this->quit = true;
    else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Down)
        this->pacMan.setValues(0, 1, 90);
    else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Up)
        this->pacMan.setValues(0, -1, 270);
    else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Left)
        this->pacMan.setValues(-1, 0, 180);
    else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Right)
        this->pacMan.setValues(1, 0, 0);
    else
        this->pacMan.setValues(0, 0, this->pacMan.getRotation());
}

void GameState::update(const float& dt)
{
    if (!this->endGame)
    {
        this->pacMan.update(dt, this->map, this->ghosts);
        for (Ghost *ghost : this->ghosts)
            ghost->update(dt, this->map);
    } else {
        this->readFile();
        if (this->pacMan.getScore() > this->highScores[4])
            this->highScore = true;
    }
    
    if (!this->pacMan.checkAlive())
        this->endGame = true;
    
    if ((this->pacMan.getEnergizerClock().getElapsedTime().asSeconds() < 5) & this->pacMan.getEnergized())
    {
        for (Ghost* ghost : ghosts)
            ghost->setEnergized(true);
    } else 
    {
        for (Ghost* ghost : ghosts)
            ghost->setEnergized(false);
    }
    


    this->health = this->pacMan.getHealth();;
    string scoreString = "score: ";
    scoreString += std::to_string(this->pacMan.getScore());
    this->currentScoreText->setString(scoreString);
    std::string endScoreString = "YOUR SCORE: ";
    endScoreString += std::to_string(this->pacMan.getScore());
    this->scoreText->setString(endScoreString);

}

void GameState::endGameDialog()
{   
    sf::Vector2f centrePos = sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2);
    this->rectangle.setSize(sf::Vector2f(300, 300));
    this->rectangle.setOrigin(sf::Vector2f(this->rectangle.getSize().x/2, this->rectangle.getSize().y/2));
    this->rectangle.setPosition(centrePos);
    sf::Color rectangleColor = sf::Color::Black;
    rectangleColor.a = 210;
    this->rectangle.setFillColor(rectangleColor);

    this->text = new sf::Text(looserFont, "looser", 30);
    sf::Color textColor = sf::Color(255,237,10);
    textColor.a = 210;
    this->text->setOrigin(sf::Vector2f(this->text->getGlobalBounds().width/2, this->text->getGlobalBounds().height/2));
    this->text->setPosition(sf::Vector2f(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2 - 100)));
    this->text->setFillColor(textColor);

    std::string scoreString = "YOUR SCORE: ";
    scoreString += std::to_string(this->pacMan.getScore());
    this->scoreText = new sf::Text(textFont, scoreString, 20);
    this->scoreText->setFillColor(textColor);
    this->scoreText->setOrigin(sf::Vector2f(this->scoreText->getGlobalBounds().width/2, this->scoreText->getGlobalBounds().height/2));
    this->scoreText->setPosition(sf::Vector2f(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2 - 60)));
    this->scoreText->setFillColor(textColor);

    this->highScoreText = new sf::Text(textFont, "You set a highscore, input name: ", 20);
    this->highScoreText->setOrigin(sf::Vector2f(this->highScoreText->getGlobalBounds().width/2, this->highScoreText->getGlobalBounds().height/2));
    this->highScoreText->setPosition(sf::Vector2f(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2 - 100)));
    this->highScoreText->setFillColor(textColor);

    

}

void GameState::readFile()
{ 
    fstream fin; 
    fin.open(this->filePath, ios::in); 

    std::string line;
    while (std::getline(fin, line)) {
            // Assuming the CSV file has two columns separated by a comma
            std::istringstream ss(line);
            std::string name;
            int value;

            // Read name and value from the CSV line
            if (std::getline(ss, name, ',') && ss >> value) {
                // Add the integer value to the list
               this->highScores.push_back(value);
            }
            
        this->leaderboard.push_back(line);
    }
    fin.close();
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->bgRect);
    this->map->render(target);
    this->pacMan.render(target);
    for (Ghost *ghost : this->ghosts)
        ghost->render(target);
    target->draw(*this->currentScoreText);
    for (int i = 0; i < this->health; i++)
        target->draw(*this->heartSprites[i]);

    if (this->endGame)
    {
        target->draw(this->rectangle);
        target->draw(*this->text);
        target->draw(*this->scoreText);
    }
    
}

#pragma GCC diagnostic pop