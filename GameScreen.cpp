#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include "ResumeScreen.hpp"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{
    setTexture(Game::bg_type);
    setbackground(bg, Game::bg_color);
}

GameScreen::GameScreen(Snake* snake){
    snake_=*snake;
    setTexture(Game::bg_type);
    setbackground(bg, Game::bg_color);
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Game::Screen = std::make_shared<ResumeScreen>(&snake_);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
    window.draw(background_base);
    window.draw(background);
    snake_.render(window);
	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}

void GameScreen::setbackground(sf::Texture &tex,sf::Color color)
{
    background.setTexture(tex);
    auto textscale=tex.getSize();
    float x= Game::Width/(float)textscale.x;
    float y= Game::Height/(float)textscale.y;
    background.setScale(x, y);
    sf::Texture t;
    t.loadFromFile("..../Snakes/Snakes/bkg_n.png");
    background_base.setTexture(t);
    sf::FloatRect bg_bound2=background_base.getLocalBounds();
    background_base.setScale(Game::Width/(float)t.getSize().x, (float)Game::Height/t.getSize().y);
    background_base.setOrigin(bg_bound2.left+bg_bound2.width/2, bg_bound2.top+bg_bound2.height/2);
    background_base.setPosition(Game::Width/2, Game::Height/2);
    background_base.setColor(color);
}


void GameScreen::setTexture(int type){
    switch (type) {
        case 1:
            bg.loadFromFile(".../Snakes/Snakes/nkgmm.png");
            break;
        case 3:
            bg.loadFromFile(".../C++_prj/Snakes/Snakes/11.png");
            break;
        default:
            bg.loadFromFile(".../C++_prj/Snakes/Snakes/1.png");
            break;
    }
}



