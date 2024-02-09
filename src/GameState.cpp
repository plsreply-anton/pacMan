#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>*)
    : State(window,states)
{

    this->pacManFont.loadFromFile("../util/fonts/pacManFont.ttf");
    this->atariFont.loadFromFile("../util/fonts/atariFont.ttf");

    this->initialHealth = this->pacMan.getHealth();
    this->health = this->pacMan.getHealth();

    this->initWorld();
    this->endGameDialog();

    if (!this->gameOverSoundBuffer.loadFromFile("../util/audio/game_over.flac"))
        cout << "ERROR LOADING SOUND" << endl;
    this->gameOverSound = new sf::Sound(this->gameOverSoundBuffer);

    if (!this->lifeLostBuffer.loadFromFile("../util/audio/lifeLost2.flac"))
        cout << "ERROR LOADING SOUND" << endl;
    this->lifeLostSound = new sf::Sound(this->lifeLostBuffer);

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
    delete this->gameOverSound;
    delete this->lifeLostSound;
}

void GameState::initWorld()
{
    this->map = new Map();
    this->map->loadMapFromFile();
    this->map->initTiles();
    this->initStatusbar();

    ghosts.push_back(new Blinky(sf::Vector2f(10*40+20, 9*40+20)));
    ghosts.push_back(new Inky(sf::Vector2f(9*40+20, 10*40+20)));
    ghosts.push_back(new Pinky(sf::Vector2f(10*40+20, 10*40+20)));
    ghosts.push_back(new Clyde(sf::Vector2f(11*40+20, 10*40+20)));
}

void GameState::initStatusbar()
{
    this->statusbarRectangle.setFillColor(sf::Color::Black);
    this->statusbarRectangle.setPosition(sf::Vector2f(0,840));
    this->statusbarRectangle.setSize(sf::Vector2f(840, 40));
    this->currentScoreText = new sf::Text(atariFont, "score: 0", 20);
    this->currentScoreText->setPosition(sf::Vector2f(20, 850));

    this->heartTexture.loadFromFile("../util/sprites/heart.png");

    for (int i = 0; i < this->health; i++)
    {
        heartSprites.push_back(new sf::Sprite(this->heartTexture));
        heartSprites[i]->setScale(sf::Vector2f(0.1, 0.1));
        heartSprites[i]->setPosition(sf::Vector2f(600 + i * 20, 850));
    }
}

void GameState::endState() const
{
    std::cout << "Ending Game State" << std::endl;
}

void GameState::updateInput(const float& dt, const sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        switch (ev.key.code)
        {
            case sf::Keyboard::Space:
                this->quit = true;
                break;
            case sf::Keyboard::Down:
                this->pacMan.setValues(0, 1, 90);
                break;
            case sf::Keyboard::Up:
                this->pacMan.setValues(0, -1, 270);
                break;
            case sf::Keyboard::Left:
                this->pacMan.setValues(-1, 0, 180);
                break;
            case sf::Keyboard::Right:
                this->pacMan.setValues(1, 0, 0);
                break;
            default:
                this->pacMan.setValues(0, 0, this->pacMan.getRotation());
                break;
        }
    }
    
    if (highScore_ && ev.type == sf::Event::TextEntered)
    {
        if (ev.text.unicode < 128)  
        {  
            this->playerName->setString(string((this->playerName->getString()) + static_cast<char>(ev.text.unicode)));
            this->playerName->setOrigin(sf::Vector2f(this->playerName->getGlobalBounds().width/2, this->playerName->getGlobalBounds().height/2));
            this->playerName->setPosition(sf::Vector2f(this->window->getSize().x / 2.0f, this->window->getSize().y / 2.0f + 110));
        }
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
            ghost->update(dt, this->map, this->pacMan.getSpritePointer()->getPosition(), this->currentMode);

        if (!this->pacMan.checkAlive() || (this->map->getTotalPellets() == this->pacMan.getCollectedPellets()))
            this->endGame = true;

        this->health = this->pacMan.getHealth();

        if (this->pacMan.getCoolDownClock().getElapsedTime().asMilliseconds() < 1000 && this->health != this->initialHealth)
        {   
            if (this->lifeLostSound->getStatus() != sf::Sound::Status::Playing && this->pacMan.getCoolDownClock().getElapsedTime().asMilliseconds() < 50)
            {
                this->lifeLostSound->play();
            }
            
            if (this->blinkClock.getElapsedTime().asMilliseconds() < 100)
                this->statusbarRectangle.setFillColor(sf::Color::Black);
            else if (this->blinkClock.getElapsedTime().asMilliseconds() < 200)
                this->statusbarRectangle.setFillColor(sf::Color::Red);
            else
                this->blinkClock.restart();
        }
        else 
        {
            this->statusbarRectangle.setFillColor(sf::Color::Black);
        }

    } else
    {
        if (this->gameOverSound->getStatus() != sf::Sound::Status::Playing && !this->gameOverSoundPlayed)
        {
            this->gameOverSound->play();
            
        } else {
            this->gameOverSoundPlayed = true;
        }
        
        
        if (!fileRead)
        {
            this->readFile();

            if (this->pacMan.getScore() > this->highScores[4].score)
                this->highScore_ = true;
        }
    } 
    
    string scoreString = "score: " + std::to_string(this->pacMan.getScore());
    this->currentScoreText->setString(scoreString);
    std::string endScoreString = "YOUR SCORE: " + std::to_string(this->pacMan.getScore());
    this->scoreText->setString(endScoreString);
}

void GameState::endGameDialog()
{   
    const sf::Vector2u windowSize = this->window->getSize();
    const sf::Vector2f centrePos = sf::Vector2f(static_cast<float>(windowSize.x) / 2.0f, static_cast<float>(windowSize.y) / 2.0f);

    // Configure background rectangle
    this->rectangle.setSize(sf::Vector2f(300, 300));
    this->rectangle.setOrigin(this->rectangle.getSize() / 2.0f);
    this->rectangle.setPosition(centrePos);
    sf::Color rectangleColor = sf::Color::Black;
    rectangleColor.a = 210;
    this->rectangle.setFillColor(rectangleColor);

    // Configure "looser" text
    this->text = new sf::Text(pacManFont, "looser", 40);
    sf::Color textColor = sf::Color(255,237,10);
    textColor.a = 210;
    this->text->setOrigin(sf::Vector2f(this->text->getGlobalBounds().width / 2.0f, this->text->getGlobalBounds().height / 2.0f));
    this->text->setPosition(centrePos - sf::Vector2f(0, 100));
    this->text->setFillColor(textColor);

    // Configure score texts
    string scoreString = "YOUR SCORE: " + to_string(this->pacMan.getScore());
    this->scoreText = new sf::Text(atariFont, scoreString, 20);
    this->scoreText->setFillColor(textColor);
    this->scoreText->setOrigin(sf::Vector2f(this->scoreText->getGlobalBounds().width / 2.0f, this->scoreText->getGlobalBounds().height / 2.0f));
    this->scoreText->setPosition(centrePos - sf::Vector2f(0, 60));

    // Configure high score text
    this->highScoreText = new sf::Text(atariFont, "You set a highscore, input name: ", 20);
    this->highScoreText->setOrigin(sf::Vector2f(this->highScoreText->getGlobalBounds().width / 2.0f, this->highScoreText->getGlobalBounds().height / 2.0f));
    this->highScoreText->setPosition(centrePos + sf::Vector2f(0, 80));
    this->highScoreText->setFillColor(textColor);

    // Configure player name text
    this->playerName->setOrigin(sf::Vector2f(this->playerName->getGlobalBounds().width / 2.0f, this->playerName->getGlobalBounds().height / 2.0f));
    this->playerName->setPosition(centrePos + sf::Vector2f(0, 110));
    this->playerName->setPosition(centrePos + sf::Vector2f(0, 110));
    this->playerName->setFillColor(textColor);

    // Configure player name input rectangle
    sf::Color rectColor = sf::Color(10,10,10);
    rectColor.a = 250;
    this->playerNameRectangle.setFillColor(rectColor);
    this->playerNameRectangle.setSize(sf::Vector2f(120, 25));
    this->playerNameRectangle.setOrigin(sf::Vector2f(this->playerNameRectangle.getGlobalBounds().width / 2.0f, this->playerNameRectangle.getGlobalBounds().height / 2.0f));;
    this->playerNameRectangle.setPosition(centrePos + sf::Vector2f(0, 115));
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
    if ((this->pacMan.getEnergizerClock().getElapsedTime().asSeconds() < 5) && this->pacMan.getEnergized())
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