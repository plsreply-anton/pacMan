#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initialHealth = this->pacMan.getHealth();
    this->health = this->pacMan.getHealth();

    this->bgRect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->bgRect.setFillColor(sf::Color::Black);
    this->paused = false;
    this->initWorld();
    
    this->looserFont.loadFromFile("../util/PacfontGood.ttf");
    this->textFont.loadFromFile("../util/SF Atarian System.ttf");
    ghosts.push_back(new Blinky(sf::Vector2f(160, 60)));
    ghosts.push_back(new Inky(sf::Vector2f(740, 760)));
    ghosts.push_back(new Pinky(sf::Vector2f(740, 60)));
    ghosts.push_back(new Clyde(sf::Vector2f(160, 760)));
    this->endGameDialog();
    this->playerName->setString(" ");
    std::cout << "New Game State" << std::endl;
}

GameState::~GameState()
{
    for (Ghost *ghost : this->ghosts)
        delete ghost;

    this->ghosts.clear();
    this->endState(); 

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
    this->statusbarRectangle.setFillColor(sf::Color::Black);
    this->statusbarRectangle.setPosition(sf::Vector2f(0,840));
    this->statusbarRectangle.setSize(sf::Vector2f(840, 40));
    this->font.loadFromFile("../util/SF Atarian System.ttf");
    this->font.setSmooth(true);
    this->currentScoreText = new sf::Text(font, "score: 0", 20);
    this->currentScoreText->setPosition(sf::Vector2f(20, 850));

    this->heartTexture.loadFromFile("../util/heart.png");

    for (int i = 0; i < this->health; i++)
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
    
    if (highScore_ && ev.type == sf::Event::TextEntered)
    {
        if (ev.text.unicode < 128)    
            this->playerName->setString(string((this->playerName->getString()) + static_cast<char>(ev.text.unicode)));
        
        this->playerName->setOrigin(sf::Vector2f(this->playerName->getGlobalBounds().width/2, this->playerName->getGlobalBounds().height/2));
        this->playerName->setPosition(sf::Vector2f(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2 + 110)));
    }

    if (highScore_ && ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
    {
        this->writeHighScore();
        this->quit = true;
    }
}

void GameState::update(const float& dt)
{
    this->updateGhostMode();
    if (!this->endGame)
    {
        
        this->pacMan.update(dt, this->map, this->ghosts);
        for (Ghost *ghost : this->ghosts)
        {
            ghost->update(dt, this->map, this->pacMan.getSpritePointer()->getPosition(), this->currentMode);
            
        }    
    } else if (!fileRead){
        this->readFile();
        if (this->pacMan.getScore() > this->highScores[4].score)
            this->highScore_ = true;
    }
    
    if (!this->pacMan.checkAlive())
        this->endGame = true;

    this->health = this->pacMan.getHealth();
    if (this->pacMan.getCoolDownClock().getElapsedTime().asMilliseconds() < 1000 && this->health != this->initialHealth)
    {   
        if (this->blinkClock.getElapsedTime().asMilliseconds() < 100)
            this->statusbarRectangle.setFillColor(sf::Color::Black);
        else if (this->blinkClock.getElapsedTime().asMilliseconds() < 200)
            this->statusbarRectangle.setFillColor(sf::Color::Red);
        else
             this->blinkClock.restart();
    } else {
        this->statusbarRectangle.setFillColor(sf::Color::Black);
    }
    
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

    this->text = new sf::Text(looserFont, "looser", 40);
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
    this->highScoreText->setPosition(sf::Vector2f(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2 + 80)));
    this->highScoreText->setFillColor(textColor);

    this->playerName->setOrigin(sf::Vector2f(this->playerName->getGlobalBounds().width/2, this->playerName->getGlobalBounds().height/2));
    this->playerName->setPosition(sf::Vector2f(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2 + 110)));
    this->playerName->setFillColor(textColor);

    sf::Color rectColor = sf::Color(10,10,10);
    rectColor.a = 250;
    this->playerNameRectangle.setFillColor(rectColor);
    this->playerNameRectangle.setSize(sf::Vector2f(120, 25));
    this->playerNameRectangle.setOrigin(sf::Vector2f(this->playerNameRectangle.getGlobalBounds().width/2, this->playerNameRectangle.getGlobalBounds().height/2));
    this->playerNameRectangle.setPosition(sf::Vector2f(sf::Vector2f(this->window->getSize().x/2, this->window->getSize().y/2 + 115)));
}

void GameState::writeHighScore()
{
    ScoreData newScoreData{string(this->playerName->getString()+ ", " + to_string(this->pacMan.getScore())), this->pacMan.getScore()};
    // Insert the new score into the vector in descending order
    this->highScores.insert(
        upper_bound(this->highScores.begin(), this->highScores.end(), newScoreData,
                         [](const ScoreData& a, const ScoreData& b) {
                             return a.score > b.score;
                         }),
        newScoreData);
    this->highScores.pop_back();
    ofstream outputFile(filePath, std::ios::trunc); //(truncating it)

    if (!outputFile.is_open())
        std::cerr << "Error opening file for writing." << endl;

    for (const auto &scoreData : highScores) {
        outputFile << scoreData.line << '\n';
    }
    outputFile.close();
}

void GameState::readFile()
{ 
    // Open the CSV file for reading
    ifstream inputFile(this->filePath);
    if (!inputFile.is_open())
        cerr << "Error opening file." << endl;

    // Read the file into a vector of ScoreData
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string name;
        int score;
        if (iss >> name >> score)
            this->highScores.push_back({line, score});
        else
            cerr << "Error parsing line: " << line << endl;
    }    
    this->fileRead = true;
}

void GameState::updateGhostMode()
{

    if ((this->pacMan.getEnergizerClock().getElapsedTime().asSeconds() < 5) & this->pacMan.getEnergized())
    {
        this->currentMode = Frightened;
        this->modeClock.stop();
    } else {
        this->modeClock.start();
        if (this->modeClock.getElapsedTime().asSeconds() < 5)
            this->currentMode = Scatter;
        else if (this->modeClock.getElapsedTime().asSeconds() < 20)
            this->currentMode = Chase;
        else
            this->modeClock.restart();
    }
    
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
    target->draw(this->statusbarRectangle);
    target->draw(*this->currentScoreText);
    for (int i = 0; i < this->health; i++)
        target->draw(*this->heartSprites[i]);

    if (this->endGame)
    {
        target->draw(this->rectangle);
        target->draw(*this->text);
        target->draw(*this->scoreText);
        if (this->highScore_)
        {
            target->draw(*this->highScoreText);
            target->draw(this->playerNameRectangle);
            target->draw(*this->playerName);
        }
    }
}

#pragma GCC diagnostic pop