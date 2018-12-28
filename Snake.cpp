#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include "GameOverScreen.h"
#include "GameScreen.h"
#include <math.h>

#include "Snakehead.hpp"
#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "ResumeScreen.hpp"
#include "SettingMenu.hpp"

using namespace sfSnake;

const int Snake::InitialSize = 5;
                               

Snake::Snake() : move_(0,-SnakeNode::Height),hitSelf_(false)
{
    Head_= new SnakeHead(SnakeHead(sf::Vector2f(Game::Width / 2.0-SnakeNode::Width/2.0 ,Game::Height /2.0)));
	initNodes();
    position_.x=Game::Width /2.0;
    position_.y=Game::Height /2.0;
	pickupBuffer_.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);
	dieBuffer_.loadFromFile("/Users/tr/Desktop/C++_prj/Snakes/Snakes/Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
   
}

Snake::~Snake(){
    delete Head_;
}


void Snake::updateposition(float x, float y){
    auto ptr=&position_;
    ptr->x+=x;
    ptr->y+=y;
}


void Snake::updatemove(float x,float y){
    auto ptr2=&move_;
    ptr2->x=SnakeNode::Height*(x-position_.x)/sqrt((x-position_.x)*(x-position_.x)+(y-position_.y)*(y-position_.y));
    ptr2->y=SnakeNode::Height*(y-position_.y)/sqrt((x-position_.x)*(x-position_.x)+(y-position_.y)*(y-position_.y));
}
void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(Game::Width/2.0 ,Game::Height / 2.0 + (SnakeNode::Height *(1/0.8/ 2)-1/2.0) + (SnakeNode::Height * (i+1)))));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        sf::Vector2i localPosition =sf::Mouse::getPosition(window);
        
        float x=localPosition.x;
        float y=localPosition.y;
        updatemove(x, y);
        Head_->rotateShape_(move_);
        nodes_[0].rotateShape(move_);
    }
   
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            Game::Screen = std::make_shared<GameOverScreen>(nodes_.size());
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        Game::Screen=std::make_shared<SettingMenuScreen>();
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)//&it
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
        if(toRemove->getcolor()==sf::Color::Red)
            grow(3);
        else if(toRemove->getcolor()==sf::Color::Green)
            grow(2);
        else if(toRemove->getcolor()==sf::Color::Blue)
            grow(1);
		fruits.erase(toRemove);
	}
}


void Snake::grow(int n)
{
    for(int i=0;i<n;++i)
        nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size()-1].getPosition().x+SnakeNode::Width*move_.x/sqrt(move_.x*move_.x+move_.y*move_.y),nodes_[nodes_.size()-1].getPosition().y+SnakeNode::Height*move_.y/sqrt(move_.x*move_.x+move_.y*move_.y))));

}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
 //   std::cout<<"hit!";
	return hitSelf_;
   
}

void Snake::checkSelfCollisions()
{

	for (decltype(nodes_.size()) i =4; i < nodes_.size(); ++i)
	{
        //if(Head_->getPosition()==nodes_[i].getPosition())
    if (Head_->getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{

    if (Head_->getPosition().x <= 0||Head_->getPosition().x >= Game::Width||Head_->getPosition().y <= 0||Head_->getPosition().y >= Game::Height)
        Game::Screen = std::make_shared<GameOverScreen>(nodes_.size());
    
}

void Snake::move()
{

    for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
    {
        nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
        sf::Vector2f v=-nodes_[i].getPosition()+nodes_.at(i-1).getPosition();
        if(v.x*move_.y==v.y*move_.x){
            nodes_[i].rotateShape(move_);
        }
    }
    nodes_[0].setPosition(Head_->getPosition());
    Head_->move(move_.x, move_.y);
    updateposition(move_.x, move_.y);
}


void Snake::render(sf::RenderWindow& window)
{
    for (auto node : nodes_)
        node.render(window);
    Head_->render(window);
	
}
