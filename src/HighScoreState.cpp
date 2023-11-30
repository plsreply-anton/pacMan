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
    delete this->bgSprite;
    delete this->text;

    for (sf::Text* text : this->leaderboard)
        delete text;
    this->leaderboard.clear();
    this->endState();
}

void HighScoreState::initBackground()
{
    this->bgTexture.loadFromFile("../util/sprites/menuImage.png");
    this->bgSprite = new sf::Sprite(this->bgTexture);
}

void HighScoreState::endState() const
{
    cout << "Ending Highscore State" << endl;
}

void HighScoreState::updateInput(const float& dt, const sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
        this->quit = true;
}

void HighScoreState::initLeaderboard()
{
    this->atariFont.loadFromFile("../util/fonts/atariFont.ttf");
    this->pacManFont.loadFromFile("../util/fonts/pacManFont.ttf");
    
    sf::Vector2f rectPos = sf::Vector2f(this->window->getSize().x / 2 + 200, this->window->getSize().y / 2 + 50);
    this->rectangle.setSize(sf::Vector2f(300, 300));
    this->rectangle.setOrigin(sf::Vector2f(this->rectangle.getSize().x/2, this->rectangle.getSize().y/2));
    this->rectangle.setPosition(rectPos);
    sf::Color rectangleColor = sf::Color::Black;
    rectangleColor.a = 210;
    this->rectangle.setFillColor(rectangleColor);

    this->text = new sf::Text(this->pacManFont, "highscores", 40);
    sf::Color textColor = sf::Color(255,237,10);
    textColor.a = 210;
    this->text->setOrigin(sf::Vector2f(this->text->getGlobalBounds().width/2, this->text->getGlobalBounds().height/2));
    this->text->setPosition(sf::Vector2f(rectPos.x, rectPos.y - 125));
    this->text->setFillColor(textColor);

    this->readFile();
}

void HighScoreState::readFile()
{ 
    fstream fin; 
    fin.open(this->filePath, ios::in); 

    string line, word, temp;
    int i = 0;
  
    while (fin) { 
        temp.clear();
  
        getline(fin, line); 
        stringstream s(line); 

        while (getline(s, word, ','))
            temp += word;
            
        this->leaderboard.push_back(new sf::Text(atariFont, temp, 25));
        this->leaderboard[i]->setOrigin(sf::Vector2f(this->leaderboard[i]->getGlobalBounds().width/2, this->leaderboard[i]->getGlobalBounds().height/2));
        this->leaderboard[i]->setPosition(sf::Vector2f(this->window->getSize().x/2 + 200, this->window->getSize().y/2-40 + i*50));
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
    target->draw(this->rectangle);
    target->draw(*this->text);

    for (int i = 0; i < 5; i++)
        target->draw(*this->leaderboard[i]);
}

#pragma GCC diagnostic pop