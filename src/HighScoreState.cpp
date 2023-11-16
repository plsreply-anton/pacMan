#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "HighScoreState.h"

HighScoreState::HighScoreState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initBackground();
    this->initLeaderboard();
    std::cout << "New Highscore State" << std::endl;
}

HighScoreState::~HighScoreState()
{
    this->endState();
    delete this->bgSprite;
    delete this->backArrowSprite;
    delete this->text;
    for (sf::Text* text : this->leaderboard)
        delete text;
    this->leaderboard.clear();
}

void HighScoreState::initBackground()
{
    this->bgTexture.loadFromFile("../util/menuImage.png");
    this->bgTexture.setSmooth(true);
    this->bgSprite = new sf::Sprite(this->bgTexture);

    this->backArrowTexture.loadFromFile("../util/BackArrow.png");
    this->backArrowTexture.setSmooth(true);
    this->backArrowSprite = new sf::Sprite(this->backArrowTexture);
    this->backArrowSprite->setPosition(sf::Vector2f(20,830));
}

void HighScoreState::endState()
{
    std::cout << "Ending Highscore State" << std::endl;
}

void HighScoreState::updateInput(const float& dt, sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
        this->quit = true;
}

void HighScoreState::initLeaderboard()
{
    this->leaderboardFont.loadFromFile("../util/SF Atarian System.ttf");
    this->headerFont.loadFromFile("../util/PacfontGood.ttf");
    int pos_x = ((sf::Vector2u(this->window->getSize()).x - 200)/2)+130;
    int pos_y = 340;
    this->shape.setPosition(sf::Vector2f(pos_x,pos_y));
    this->shape.setSize(sf::Vector2f(200, 50));
    this->shape.setFillColor(this->buttonColor);
    this->text = new sf::Text(headerFont, "highscores", 20);
    this->text->setFillColor(this->textColor);
    this->text->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f)));
    this->readFile();
}

void HighScoreState::readFile()
{ 
    fstream fin; 
    fin.open(this->filePath, ios::in); 

    // Read the Data from the file 
    // as String Vector 
    string line, word, temp;
    int i = 0;
  
    while (fin) { 

        temp.clear();
  
        // read an entire row and 
        // store it in a string variable 'line' 
        getline(fin, line); 
  
        // used for breaking words 
        stringstream s(line); 
  
        // read every column data of a row and store it in a string variable, 'word' 
        while (getline(s, word, ',')) { 
  
            // add all the column data of a row to a vector 
            temp += word;
        } 
        this->leaderboard.push_back(new sf::Text(leaderboardFont, temp, 20));
        this->leaderboard[i]->setPosition(sf::Vector2f(525, 400 + i*40));
        this->leaderboard[i]->setFillColor(this->textColor);
        i ++;
    }
}

void HighScoreState::update(const float& dt)
{
    //this->updateInput(dt);
}

void HighScoreState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(*this->bgSprite);
    target->draw(this->shape);
    target->draw(*this->text);
    for (int i = 0; i < 5; i++)
    {
        target->draw(*this->leaderboard[i]);
    }
    target->draw(*this->backArrowSprite);
}

#pragma GCC diagnostic pop