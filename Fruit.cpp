#include <SFML/Graphics.hpp>
#include<cstdlib>
#include<ctime>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

Fruit::Fruit(sf::Vector2f position)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
    srand((unsigned)time(NULL));
    int* p=new int(rand()%100);
    if(*p<0&&*p>100){
        throw "Wrong!";
    }
    else if(*p>=25){
        if(*p%3==0)
            shape_.setFillColor(sf::Color::Red);
        if(*p%3==1)
            shape_.setFillColor(sf::Color::Yellow);
        if(*p%3==2)
            shape_.setFillColor(sf::Color::Green);}
    else
        *p%2==0?shape_.setFillColor(sf::Color::Black):shape_.setFillColor(sf::Color(139,26,26));
    delete p;
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::Color Fruit::getcolor() const
{
    return shape_.getFillColor();
}
sf::FloatRect Fruit::getBounds() const
{
    return shape_.getGlobalBounds();
}
