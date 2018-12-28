//
//  Snakehead.hpp
//  Snakes
//
//  Created by 田睿 on 2018/7/1.
//  Copyright © 2018年 田睿. All rights reserved.
//

#ifndef Snakehead_hpp
#define Snakehead_hpp
#include "SnakeNode.h"

namespace sfSnake
{
    class SnakeHead:public SnakeNode
    {
    public:
        SnakeHead(sf::Vector2f position = sf::Vector2f(0, 0));
        void setPosition(sf::Vector2f position);
        void setPosition(float x, float y);
        void setRotation (float x);
        float getRotation ();
        void rotateShape_ (float x);
        void rotateShape_ (sf::Vector2f new_v);
        void move(float xOffset, float yOffset);
        void render(sf::RenderWindow& window);
        sf::Vector2f getPosition() const;
        sf::FloatRect getBounds() const;
        void setHead();
    private:
        sf::Sprite shape_;
        sf::Texture texture;
        sf::Vector2f position_;
        float rotation_;
    };
}

#endif

