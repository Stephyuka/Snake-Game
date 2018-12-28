//
//  ResumeScreen.hpp
//  Snakes
//
//  Created by 田睿 on 2018/7/1.
//  Copyright © 2018年 田睿. All rights reserved.
//

#ifndef ResumeScreen_hpp
#define ResumeScreen_hpp

#include "Screen.h"
#include "Snake.h"
namespace sfSnake
{
    class ResumeScreen : public Screen
    {
    public:
        ResumeScreen(Snake* snake);
        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;
        
    private:
        Snake snake_;
        sf::Font font_;
        sf::Text text_;
        std::size_t  score_;
    };
}

#endif /* ResumeScreen_hpp */
