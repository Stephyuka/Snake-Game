#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>
#include "Game.h"
namespace sfSnake
{
class SnakeNode
{
public:
    SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0),int type=Game::snake_type,int width= SnakeNode::Width,int height=SnakeNode::Height);

	virtual void setPosition(sf::Vector2f position);
    
	virtual void setPosition(float x, float y);
    
    virtual void setRotation (float x);
    
    virtual float getRotation ();
    
    virtual void rotateShape(float x);
    
    virtual void rotateShape (sf::Vector2f v);
    
	virtual void move(float xOffset, float yOffset);

	virtual void render(sf::RenderWindow& window);
    
    virtual void setColor(int color);

	virtual sf::Vector2f getPosition() const;
	virtual sf::FloatRect getBounds() const;
    
    virtual float countAngle(sf::Vector2f v);

	static const float Width;
	static const float Height;

private:
    sf::CircleShape shape2_;
	sf::RectangleShape shape1_;
	sf::Vector2f position_;
    float rotation_;
};
}

#endif
