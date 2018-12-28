#include "ResumeScreen.hpp"
#include "Screen.h"
#include "GameScreen.h"
#include "Game.h"
#include "GameOverScreen.h"

sfSnake::ResumeScreen::ResumeScreen(Snake* snake)
{
    snake_=*snake;
    font_.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/Fonts/game_over.ttf");
    text_.setFont(font_);
    text_.setString("Continue the Game?"
                    "\n\nPress [SPACE] to continue"
                    "\n\nPress [ESC] to quit");
    text_.setColor(sf::Color::White);
    
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void sfSnake::ResumeScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        Game::Screen = std::make_shared<GameScreen>(&snake_);
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
}

void sfSnake::ResumeScreen::update(sf::Time delta)
{
    
}

void sfSnake::ResumeScreen::render(sf::RenderWindow& window)
{
    window.draw(text_);
}
