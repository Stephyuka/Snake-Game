//
//  SettingMenu.hpp
//  Snakes
//


#ifndef SettingMenu_hpp
#define SettingMenu_hpp

#include <stdio.h>
#include "GameScreen.h"
#include "Screen.h"

namespace sfSnake
{
    class SettingMenuScreen : public Screen
    {
    public:
        SettingMenuScreen();
        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;
        void initNodes();
        void setbackground(sf::Texture &bg);
        void setTextColour(sf::Color color);
        void colorFlagChange();
        void setsnake();
        void Warning_show(sf::RenderWindow &window);
        
    private:
        static bool warning_show;
        int flag;
        sf::Font font_;
        std::vector <sf::Text> text_;
        sf::Sprite background;
        sf::Sprite background_base;
        sf::Texture snake;
        sf::Texture bkg;
        sf::Color colour;
        std::vector<SnakeNode> nodes_;
        static const int initialsize;
        sf::Sprite shape_;
    };
}
#endif /* SettingMenu_hpp */
