//
//  SettingMenu.cpp
//  Snakes
//  Created by 田睿 on 2018/7/3.
//  Copyright © 2018年 田睿. All rights reserved.
//

#include "SettingMenu.hpp"
#include <string.h>
#include "Game.h"
#include "Snake.h"
#include "SnakeNode.h"
#include "MenuScreen.h"

#define type_size 5

using namespace sfSnake;

const int SettingMenuScreen::initialsize=5;

bool SettingMenuScreen::warning_show=false;


SettingMenuScreen:: SettingMenuScreen()
{
    font_.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/Fonts/Cutie Star.ttf");
    sf::Text text;
    text.setString(
                   "\nPlease Choose a Background you want:"
                   "\nEnter [B]  to Choose Black"
                   "\nEnter [W] to Choose White"
                   "\nEnter [R]  to Choose Brown");
    text_.push_back(text);
    text.setString("\n\n\nDo you want a Pattern?"
                   "\nEnter [1]  to use Pattern1 "
                   "\nEnter [2]  to use Pattern2"
                   "\nEnter [N] to go with no pattern\n\n");
    text_.push_back(text);
    text.setString("\nUse the [left]&[Right] Key \non your Keyboard to Change the Snake\n");
    text_.push_back(text);
    text.setString("Enter[Space] to Save your Change\n"
                   "And Start to enjoy your game\n");
    text_.push_back(text);
    for(decltype(text_.size())i=0;i<text_.size();++i ){
        text_[i].setFont(font_);
        sf::FloatRect textbound=text_[i].getLocalBounds();
        text_[i].setCharacterSize(30);
        text_[i].setOrigin(textbound.left+1.0/8*Game::Width, textbound.top+textbound.height/2);
        text_[i].setPosition(Game::Width/2, Game::Height/5.0*(i+1));
    }
    text_[0].setColor(sf::Color::Black);
    text_[1].setColor(sf::Color::Black);
    text_[2].setColor(sf::Color::Blue);
    text_[3].setColor(sf::Color::Blue);
    
    bkg.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/1.png");
    setbackground(bkg);
    background.setColor(sf::Color::White);
    flag=2;
    setsnake();
}

void SettingMenuScreen::render(sf::RenderWindow &window){
    window.draw(background_base);
    window.draw(background);
    for(decltype(text_.size())i=0;i<text_.size();++i){
        window.draw(text_.at(i));
    }
    window.draw(shape_);
    for (auto node : nodes_)
        node.render(window);
    Warning_show(window);
    
}

void SettingMenuScreen::setbackground(sf::Texture &bg){
    
    background.setTexture(bg);
    auto bkg_size =bg.getSize();
    background.setScale(Game::Width/(float)bg.getSize().x, (float)Game::Height/bg.getSize().y);
    sf::FloatRect bg_bound=background.getLocalBounds();
    background.setOrigin(bg_bound.left+bg_bound.width/2, bg_bound.top+bg_bound.height/2);
    background.setPosition(Game::Width/2, Game::Height/2);
    sf::Texture t;
    t.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/bkg_n.png");
    background_base.setTexture(t);
    sf::FloatRect bg_bound2=background_base.getLocalBounds();
    background_base.setScale(Game::Width/(float)t.getSize().x, (float)Game::Height/t.getSize().y);
    background_base.setOrigin(bg_bound2.left+bg_bound2.width/2, bg_bound2.top+bg_bound2.height/2);
    background_base.setPosition(Game::Width/2, Game::Height/2);
}


void SettingMenuScreen::update(sf::Time delta){
    
}
void SettingMenuScreen::initNodes()
{
    for (int i = 0; i < initialsize; ++i)
    {
        nodes_.push_back(SnakeNode(sf::Vector2f(1.0/5*Game::Width ,Game::Height*1.0/5 + (snake.getSize().y *0.2) + (snake.getSize().y*0.6*(i+1))),Game::snake_type,snake.getSize().x*0.6,snake.getSize().y*0.6));
    }
}



void SettingMenuScreen::setTextColour(sf::Color color){
    for(decltype(text_.size())i=0;i<text_.size();++i )
        text_.at(i).setFillColor(color);
}



void SettingMenuScreen::handleInput(sf::RenderWindow &window){
    colorFlagChange();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Game::Screen = std::make_shared<GameScreen>();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        Game::Screen = std::make_shared<MenuScreen>();
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if(Game::snake_type<=type_size+1){
            ++Game::snake_type;
            setsnake();
            warning_show=false;}
        else
            warning_show=true;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if(Game::snake_type>0){
            --Game::snake_type;
            setsnake();
            warning_show=false;}
        else
            warning_show=true;
    }
}


void SettingMenuScreen::Warning_show(sf::RenderWindow &window){
    if(warning_show){
        sf::Text text;
        text.setString("This is the last!");
        text.setCharacterSize(20);
        text.setFont(font_);
        text.setPosition(1.0/8*Game::Width, 6.0/8*Game::Height);
        text.setColor(sf::Color::Red);
        window.draw(text);
    }
}

void SettingMenuScreen::setsnake(){
    
    if(Game::snake_type==1){
        snake.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_1.png");
        initNodes();
    }
    else if(Game::snake_type==2){
        snake.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_2.png");
        initNodes();
    }
    else if(Game::snake_type==3){
        snake.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_3.png");
         initNodes();
    }
    else if(Game::snake_type==4){
        snake.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_4.png");
         initNodes();
    }
    else if(Game::snake_type==5){
        snake.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_5.png");
         initNodes();
    }
    else if(Game::snake_type==6){
        snake.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_6.png");
         initNodes();
    }
    
    shape_.setTexture(snake);
    sf::FloatRect snake_bound=shape_.getLocalBounds();
    shape_.setOrigin(snake_bound.left+0.5*snake_bound.width, snake_bound.top+0.5*snake_bound.height);
    shape_.setPosition(1.0/5*Game::Width, Game::Height*1.0/5);
    
    
}
void SettingMenuScreen::colorFlagChange(){
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
        background_base.setColor(sf::Color::Black);
        setTextColour(sf::Color::White);
        Game::bg_color=sf::Color::Black;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        background_base.setColor(sf::Color::White);
        Game::bg_color=sf::Color::White;
        setTextColour(sf::Color::Black);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        background_base.setColor(sf::Color(139,26,26));
        setTextColour(sf::Color::White);
        Game::bg_color=sf::Color(139,26,26);
    }
    
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
        bkg.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/nkg.png");
        setbackground(bkg);
        Game::bg_type=1;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        bkg.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/1.png");
        setbackground(bkg);
        Game::bg_type=2;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
        bkg.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/11.png");
        setbackground(bkg);
        Game::bg_type=3;
    }
}

