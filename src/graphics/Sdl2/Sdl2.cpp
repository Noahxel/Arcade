/*
** EPITECH PROJECT, 2023
** SDL2
** File description:
** arcade
*/

#include "Sdl2.hpp"

namespace arcade {

    extern "C" IGraphic* createIt(bool o)
    {
        return new graphic::SDL2(o);
    }

    namespace graphic {

        SDL2::SDL2(bool open) {
            _renderer = NULL;
            m_window = NULL;
            if (open) {
                if (SDL_Init(SDL_INIT_VIDEO) != 0)
                    throw std::runtime_error("Failed to initialize SDL2");
                this->initWindow(config::ScreenWidth, config::ScreenHeight, getName());
            }
            TTF_Init();
            m_font = TTF_OpenFont("./assets/font.ttf", 24);
            m_fontcolor = {255, 255, 255, 0};
        }

        SDL2::~SDL2()
        {
            if (_renderer)
                SDL_DestroyRenderer(this->_renderer);
            if (m_window)
                SDL_DestroyWindow(this->m_window);
            TTF_Quit();
            SDL_Quit();
        }

        void SDL2::initWindow(const int &width, const int &height, const std::string &title) noexcept {
            SDL_Init(SDL_INIT_VIDEO);
            m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
            _renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            SDL_RenderClear(_renderer);
            SDL_RenderPresent(_renderer);
        }

        void SDL2::clearWindow() const noexcept {
            SDL_RenderClear(this->_renderer);
        }

        void SDL2::updateWindow() noexcept {
            SDL_RenderPresent(_renderer);
        }

        void SDL2::drawText(const std::string& text, int x, int y, bool center) noexcept
        {
            SDL_Surface* surface = TTF_RenderText_Solid(m_font, text.c_str(), m_fontcolor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
            SDL_FreeSurface(surface);
            int text_width, text_height;
            SDL_QueryTexture(texture, nullptr, nullptr, &text_width, &text_height);

            if (center) {
                int screenWidth;
                SDL_GetRendererOutputSize(_renderer, &screenWidth, nullptr);
                x = (screenWidth - text_width) / 2;
            } else
                x *= 27;
            SDL_Rect rect = { x, y * 27, text_width, text_height };
            SDL_RenderCopy(_renderer, texture, nullptr, &rect);
            SDL_DestroyTexture(texture);
        }

        void SDL2::drawItem(const config::GameItem &item) noexcept
        {
            SDL_Texture *texture;
            SDL_Rect rect;
            int angle = 0;
            int w, h;
            rect.x = item.x * 32;
            rect.y = item.y * 32;
            rect.w = rect.h = 32;

            texture = IMG_LoadTexture(_renderer, item.itemSprite.path.c_str());
            SDL_QueryTexture(texture, NULL, NULL, &w, &h);
            SDL_RenderCopyEx(this->_renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_HORIZONTAL);
            SDL_DestroyTexture(texture);
        }

        std::string SDL2::getName() const noexcept
        {
            return "SDL2";
        }

        config::InputList SDL2::getInputEvents() noexcept
        {
            SDL_Event e;

            _events.clear();
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_QUIT:
                        _events.push_back(config::Input::EXIT);
                        break;
                    case SDL_KEYDOWN:
                        switch (e.key.keysym.sym) {
                        case SDLK_z:
                            _events.push_back(config::Input::UP);
                            break;
                        case SDLK_s:
                            _events.push_back(config::Input::DOWN);
                            break;
                        case SDLK_q:
                            _events.push_back(config::Input::LEFT);
                            break;
                        case SDLK_d:
                            _events.push_back(config::Input::RIGHT);
                            break;
                        case SDLK_m:
                            _events.push_back(config::Input::MENU);
                            break;
                        case SDLK_b:
                            _events.push_back(config::Input::PREVGAME);
                            break;
                        case SDLK_n:
                            _events.push_back(config::Input::NEXTGAME);
                            break;
                        case SDLK_h:
                            _events.push_back(config::Input::NEXTLIB);
                            break;
                        case SDLK_j:
                            _events.push_back(config::Input::PREVLIB);
                            break;
                        case SDLK_ESCAPE:
                            _events.push_back(config::Input::EXIT);
                            break;
                        case SDLK_RETURN:
                            _events.push_back(config::Input::START);
                            break;
                        default:
                            break;
                    }
                }
            }
            return _events;
        }

        void SDL2::setInputEvents() noexcept {
            SDL_StartTextInput();
        }
    }
}
