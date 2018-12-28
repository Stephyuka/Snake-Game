#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Snakehead.hpp"
#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down
	};

class Snake
{
public:
	Snake();
    ~Snake();
	void handleInput(sf::RenderWindow& window);
    void updatemove(float x,float y);
    void updateposition(float x,float y);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;
    sf::Event event;

	unsigned getSize() const;

private:
    void move();
	void grow(int i);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

    sf::Vector2f position_;
    sf::Vector2f move_old;
    sf::Vector2f move_;
	Direction direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;
    SnakeHead* Head_;
	std::vector<SnakeNode> nodes_;

	static const int InitialSize;
};
    
}

#endif
