/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Sfml
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "IGraphic.hpp"

extern "C" __attribute__((visibility("default"))) const char graphicflag[] = "graphic";

namespace arcade {
    extern "C" IGraphic* createIt(bool);
    namespace graphic {
        class Sfml : public IGraphic {
            public:
                Sfml(bool);
                void initWindow(const int &, const int &, const std::string &) noexcept;
                void clearWindow() const noexcept;
                void updateWindow() noexcept;
                void drawText(const std::string &, int, int, bool) noexcept;
                void drawItem(const config::GameItem &) noexcept;
                void setAnimationStep(uint) noexcept;
                void setInputEvents() noexcept;
                config::InputList getInputEvents() noexcept;
                std::string getName() const noexcept;

            protected:
            private:
                std::unique_ptr<sf::RenderWindow> _window;
                config::InputList _events;
                sf::Text _text;
                sf::Font _font;
        };
    }
}
