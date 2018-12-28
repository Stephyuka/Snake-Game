#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingMenu.hpp"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
	font_.loadFromFile(".../Snakes/Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit");
    
	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);
    
    bg_setting.setFont(font_);
    bg_setting.setString("\n Settings\n"  );
    bg_setting.setColor(sf::Color::White);
    bg_setting.setCharacterSize(25);
    
	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
    
    sf::FloatRect bgsettingBounds =bg_setting.getLocalBounds();
    bg_setting.setOrigin(bgsettingBounds.left+bgsettingBounds.width/2, bgsettingBounds.top+bgsettingBounds.height/2);
    bg_setting.setPosition(Game::Width/2, Game::Height*7/8);
    set_click=bg_setting.getGlobalBounds();
    
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
    
    sf::Vector2i v=sf::Mouse::getPosition(window);
    if((v.x>set_click.left&&v.x<set_click.left+set_click.width)&&(v.y>set_click.top&&v.y<set_click.top+set_click.height)){
        bg_setting.setCharacterSize(28);
        bg_setting.setStyle(sf::Text::Bold);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            Game::Screen=std::make_shared<SettingMenuScreen>();
        }
    }
    else
        bg_setting.setCharacterSize(25);
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(snakeText_);
    window.draw(bg_setting);
}
