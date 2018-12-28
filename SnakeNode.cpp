#include <SFML/Graphics.hpp>
#include <math.h>
#include "SnakeNode.h"
#include "Snake.h"
#define PI 3.1415926

using namespace sfSnake;

const float SnakeNode::Width = 12.f;
const float SnakeNode::Height = 12.f;

SnakeNode::SnakeNode(sf::Vector2f position,int type,int width,int height)
: position_(position)
{
    setColor(type);
    shape2_.setRadius(width*0.5);
	shape1_.setSize(sf::Vector2f(width, height*0.3));
    shape1_.setRotation(0);
    sf::FloatRect v= shape1_.getLocalBounds();
    shape1_.setOrigin(v.left+v.width/2.0, v.top+v.height/2.0);
    v=shape2_.getLocalBounds();
    shape2_.setOrigin(v.left+v.width/2.0, v.top+v.height/2.0);
    shape1_.setPosition(position_);
    shape2_.setPosition(position_);
}

void SnakeNode::setColor(int snake_type){
    if(snake_type==1){
        shape1_.setFillColor(sf::Color(230,164,51));
        shape2_.setFillColor(sf::Color(252,233,178));
    }
    else if(snake_type==2){
        shape1_.setFillColor(sf::Color(29,94,197));
        shape2_.setFillColor(sf::Color(233,90,108));
    }
    else if(snake_type==3){
        shape1_.setFillColor(sf::Color(81,130,33));
        shape2_.setFillColor(sf::Color(72,27,13));
    }
    else if(snake_type==4){
        shape1_.setFillColor(sf::Color(232,91,191));
        shape2_.setFillColor(sf::Color(79,64,142));
    }
    else if(snake_type==5){
        shape1_.setFillColor(sf::Color(229,32,39));
        shape2_.setFillColor(sf::Color(55,38,35));
    }
    else if(snake_type==6){
        shape1_.setFillColor(sf::Color(0,0,0));
        shape1_.setFillColor(sf::Color(27,68,55));
    }
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape1_.setPosition(position_);
    shape2_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
    shape2_.setPosition(position_);
	shape1_.setPosition(position_);
}
float SnakeNode::getRotation(){
    return shape1_.getRotation();
    
}
void SnakeNode::setRotation(float x){
    shape1_.setRotation(x);
    shape2_.setRotation(x);
    rotation_=x;
}

void SnakeNode::rotateShape(float alpha){
    shape1_.setRotation(alpha);
    shape2_.setRotation(alpha);
}

void SnakeNode::rotateShape(sf::Vector2f v){
    float y= countAngle(v);
    setRotation(-y+90);
}


void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape1_.setPosition(position_);
    shape2_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
    sf::FloatRect y=shape2_.getGlobalBounds();
    float z=y.width;
    z=y.left;
	return shape1_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
    window.draw(shape2_);
	window.draw(shape1_);
}
float SnakeNode::countAngle(sf::Vector2f v){
    if(v.x>0&&v.y>=0)
        return 2-atan(v.y/v.x)/PI*180;
    else if(v.x>0&&v.y<0)
        return atan(-v.y/v.x)/PI*180;
    else if(v.x<0)
        return 180-atan(v.y/v.x)/PI*180;
    else if((v.x==0&&v.y<0))
        return 90;
    else if(v.x==0&&v.y>0)
        return 270;
    else
        throw "There exists no angle!";
}

