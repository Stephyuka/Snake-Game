#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();
    GameScreen(Snake* snake_);
	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;
	void generateFruit();
    void setbackground(sf::Texture &t,sf::Color color);
    void setTexture(int type);
    
private:
    sf::Sprite background;
    sf::Sprite background_base;
	Snake snake_;
	std::vector<Fruit> fruit_;
    sf::Texture bg;
};
    
}

#endif
