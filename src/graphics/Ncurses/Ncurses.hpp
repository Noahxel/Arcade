/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Ncurses
*/

#pragma once

#include <thread>
#include <iostream>
#include <ncurses.h>
#include "IGraphic.hpp"

extern "C" __attribute__((visibility("default"))) const char graphicflag[] = "graphic";

namespace arcade {
    extern "C" IGraphic* createIt(bool);
    namespace graphic {
        class Ncurses : public IGraphic {
            public:
                Ncurses(bool);
                ~Ncurses();
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
                WINDOW *_window;
                config::InputList _inputList;
        };
    }
}
