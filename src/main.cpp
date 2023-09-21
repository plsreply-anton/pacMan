#include <SFML/Graphics.hpp>

int main() {

	sf::Vector2u windowSize(800, 600);
    sf::RenderWindow window(sf::VideoMode(windowSize), "My window");
    window.setTitle("SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("../util/bg.jpg"))
        return EXIT_FAILURE;
    sf::Sprite enemySprite(texture);

    enemySprite.setTexture(texture);    
    enemySprite.scale(sf::Vector2f(1,1));

    
	// run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(enemySprite); // Draw the sprite here
        window.display();
    }
    return 0;
}
