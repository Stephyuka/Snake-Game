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

using namespace sfSnake;

const int Snake::InitialSize = 5;
                               
void Snake::updateposition(float x, float y){
    auto ptr=&position_;
    ptr->x+=x;
    ptr->y+=y;
}


void Snake::updatemove(float x,float y){
    auto ptr2=&move_;
    auto ptr1=&move_old;
    *ptr1=*ptr2;
    ptr2->x=12*(x-position_.x)/sqrt((x-position_.x)*(x-position_.x)+(y-position_.y)*(y-position_.y));
    ptr2->y=12*(y-position_.y)/sqrt((x-position_.x)*(x-position_.x)+(y-position_.y)*(y-position_.y));
}

Snake::Snake() : move_(0,-12),move_old(0,10),hitSelf_(false)
{
    Head_= new SnakeHead(SnakeHead(sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,Game::Height / 2 - (SnakeNode::Height / 2))));
	initNodes();
    position_.x=Game::Width / 2 - SnakeNode::Width / 2;
    position_.y=Game::Height / 2 - (SnakeNode::Height/2);
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

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(Game::Width / 2 - SnakeNode::Width / 2,Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * (i+1)))));
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            Game::Screen = std::make_shared<ResumeScreen>(nodes_.size());
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            Game::Screen = std::make_shared<GameOverScreen>(nodes_.size());
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
		grow();
		fruits.erase(toRemove);
	}
}
void Snake::nodesrotate(sfSnake::SnakeNode *v){
    if(nodes_.size()!=0)
        v->rotateShape((v-1)->getRotation());
}
void Snake::grow()
{
    nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size()-1].getPosition().x+SnakeNode::Width*move_.x/sqrt(move_.x*move_.x+move_.y*move_.y),nodes_[nodes_.size()-1].getPosition().y+SnakeNode::Height*move_.y/sqrt(move_.x*move_.x+move_.y*move_.y))));

}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
    std::cout<<"hit!";
	return hitSelf_;
   
}

void Snake::checkSelfCollisions()
{

	for (decltype(nodes_.size()) i = 4; i < nodes_.size(); ++i)
	{
        if(Head_->getPosition()==nodes_[i].getPosition())
   //     if (Head_->getBounds().intersects(nodes_[i].getBounds()))
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
    
		//headNode.setPosition(Game::Width, headNode.getPosition().y);
	/*else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);*/
}

void Snake::move()
{
/*    sf::Event event;
    if(event.type==sf::Event::MouseMoved){
            sf::Vector2i localPosition =sf::Mouse::getPosition();
            move_.x=10*(localPosition.x-position_.x)/sqrt((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));
            move_.y=10*(localPosition.y-position_.y)/sqrt((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));//}
    }*/
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
    Head_->render(window);
	for (auto node : nodes_)
		node.render(window);
}
/* if(window.pollEvent(event)){
 if(event.type==sf::Event::MouseButtonPressed){
 sf::Vector2i localPosition =sf::Mouse::getPosition();
 move_.x=10*(localPosition.x-position_.x)/sqrt((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));
 move_.y=10*(localPosition.y-position_.y)/sqrt((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));
 }*/
/* if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
 direction_ = Direction::Up;
 //     for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
 //   nodes_[i].rotateTriangle(90);
 }
 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
 direction_ = Direction::Down;
 //     for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
 //   nodes_[i].rotateTriangle(90);
 }
 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
 direction_ = Direction::Left;
 //     for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
 //   nodes_[i].rotateTriangle(90);
 }
 else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
 direction_ = Direction::Right;
 //     for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
 //   nodes_[i].rotateTriangle(90);
 }*/

/*if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
 sf::Vector2i localPosition =sf::Mouse::getPosition();
 move_.x=10*(localPosition.x-position_.x)/sqrt((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));
 move_.y=10*(localPosition.y-position_.y)/sqrt((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));
 }*/
/*switch (direction_)
 {
 case Direction::Up:
 nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
 // nodesrotate(&nodes_[nodes_.size() - 1]);
 break;
 case Direction::Down:
 nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
 nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
 // nodesrotate(&nodes_[nodes_.size() - 1]);
 break;
 case Direction::Left:
 nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,nodes_[nodes_.size() - 1].getPosition().y)));
 // nodesrotate(&nodes_[nodes_.size() - 1]);
 break;
 case Direction::Right:
 nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,nodes_[nodes_.size() - 1].getPosition().y)));
 // nodesrotate(&nodes_[nodes_.size() - 1]);
 break;}*/
/*
 sf::Vector2i localPosition = sf::Mouse::getPosition();
 move_.x=(localPosition.x-position_.x)/((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));
 move_.y=(localPosition.y-position_.y)/((localPosition.x-position_.x)*(localPosition.x-position_.x)+(localPosition.y-position_.y)*(localPosition.y-position_.y));
 

 for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
 {
 nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
 }
 
 switch (direction_)
 {
 
 case Direction::Up:
 nodes_[0].move(0, -SnakeNode::Height);
 break;
 case Direction::Down:
 nodes_[0].move(0, SnakeNode::Height);
 break;
 case Direction::Left:
 nodes_[0].move(-SnakeNode::Width, 0);
 break;
 case Direction::Right:
 nodes_[0].move(SnakeNode::Width, 0);
 break;
 }
 */
