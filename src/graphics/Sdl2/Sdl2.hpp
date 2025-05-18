/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** SDL2
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "../../../src/Interfaces/IGraphic.hpp"
extern "C" __attribute__((visibility("default"))) const char graphicflag[] = "graphic";

namespace arcade {
    extern "C" IGraphic* createIt(bool);
    namespace graphic {
        class SDL2 : public IGraphic {
            public:
                SDL2(bool);
                ~SDL2();
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
                SDL_Window *m_window;
                SDL_Renderer *_renderer;
                uint m_animationStep;
                config::InputList m_inputEvents;
                bool m_inputEventSet;
                config::InputList _events;
                TTF_Font* m_font;
                SDL_Color m_fontcolor;
        };
    }
}
