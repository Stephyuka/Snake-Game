//
//  Snakehead.cpp
//  Snakes
//
//  Created by 田睿 on 2018/7/1.
//  Copyright © 2018年 田睿. All rights reserved.
//

#include "Snakehead.hpp"
#include "SnakeNode.h"
#include <math.h>
#define PI 3.1415926

using namespace sfSnake;
SnakeHead::SnakeHead(sf::Vector2f position){
    position_=position;
    setHead();
    shape_.setPosition(position_);
    shape_.setRotation(0);
}

void SnakeHead::setHead(){
    if(Game::snake_type==1){
        texture.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_1.png");
    }
    else if(Game::snake_type==2){
        texture.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_2.png");
    }
    else if(Game::snake_type==3){
        texture.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_3.png");
    }
    else if(Game::snake_type==4){
        texture.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake4.png");
    }
    else if(Game::snake_type==5){
        texture.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_5.png");
    }
    else if(Game::snake_type==6){
      texture.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/snake_6.png");
    }
    else
        throw "wrong!";
    shape_.setTexture(texture);
    shape_.setScale(SnakeNode::Width/0.8/texture.getSize().x, SnakeNode::Height/0.8/texture.getSize().y);
    sf::FloatRect x=shape_.getLocalBounds();
    shape_.setOrigin(x.left+x.width/2.0, x.top+x.height/2.0);
    
}
void SnakeHead::setPosition(sf::Vector2f position)
{
    position_ = position;
    shape_.setPosition(position_);
}

void SnakeHead::setPosition(float x, float y){
    position_.x=x;
    position_.y=y;
    shape_.setPosition(position_);
}
sf::Vector2f SnakeHead::getPosition() const{
    return position_;
}

void SnakeHead::setRotation(float x){
    shape_.setRotation(x);
    rotation_=x;
}
float SnakeHead::getRotation(){
    return shape_.getRotation();
}


void SnakeHead::rotateShape_(sf::Vector2f new_v){
    float y= countAngle(new_v);
    setRotation(-y+90);
//
}
void SnakeHead::move(float xOffset, float yOffset)
{
    position_.x += xOffset;
    position_.y += yOffset;
    shape_.setPosition(position_);
}

sf::FloatRect SnakeHead::getBounds() const
{
    sf::FloatRect x=shape_.getGlobalBounds();
    float y=x.left;
    y=x.height;
    y=x.top;
    y=x.width;
    return shape_.getGlobalBounds();
}

void SnakeHead::render(sf::RenderWindow& window)
{
    window.draw(shape_);
}

