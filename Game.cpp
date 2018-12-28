#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

int Game::bg_type=2;
int Game::snake_type=1;
sf::Color Game::bg_color=sf::Color::White;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile(".../Snakes/Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}


void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
        
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

//void Game::checkWindow(){
  //  sf::Event event;
 //   if(window_.pollEvent(event))
 //       return event;
//}

void Game::render()
{
    sf::Event event;
    if(window_.pollEvent(event)){
        window_event=event;
    }
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}
