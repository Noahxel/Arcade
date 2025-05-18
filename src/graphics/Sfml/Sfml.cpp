/*
** EPITECH PROJECT, 2023
** Sfml
** File description:
** arcade
*/

#include "Sfml.hpp"

namespace arcade
{
    extern "C" IGraphic* createIt(bool o) {
        return new graphic::Sfml(o);
    }
    namespace graphic
    {
        Sfml::Sfml(bool o)
        {
            if (o) {
                initWindow(config::ScreenHeight, config::ScreenWidth, "SFML");
                _font.loadFromFile("./assets/font.ttf");
                _text.setFont(_font);
                _text.setPosition(0, 0);
            }
        }

        void Sfml::initWindow(const int &width, const int &height, const std::string &title) noexcept
        {
            _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
            _window->setFramerateLimit(60);
        }

        void Sfml::clearWindow() const noexcept
        {
            _window->clear(sf::Color::Black);
        }

        void Sfml::updateWindow() noexcept
        {
            _window->display();
        }

        void Sfml::drawText(const std::string& str, int x, int y, bool center) noexcept
        {
            _text.setString(str);
            int textWidth = _text.getLocalBounds().width;
            const sf::Color white = sf::Color::White;

            if (center) {
                int screenWidth = _window->getSize().x;
                x = (screenWidth - textWidth) / 2;
            } else
                x *= 27;
            _text.setFont(_font);
            _text.setFillColor(white);
            _text.setPosition(x, (y * 27) + 12);
            _window->draw(_text);
        }
        void Sfml::drawItem(const config::GameItem& item) noexcept
        {
            sf::Texture text;
            float x = item.x * 32 + 16;
            float y = item.y * 32 + 16;

            text.loadFromFile(item.itemSprite.path.c_str());
            sf::Sprite sprite(text);
            sprite.setPosition(x, y);
            _window->draw(sprite);
        }

        std::string Sfml::getName() const noexcept {
            return "Sfml";
        }

        config::InputList Sfml::getInputEvents() noexcept
        {
            sf::Event event;

            _events.clear();
            while (_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _events.push_back(config::Input::EXIT);
                } else if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Z:
                            _events.push_back(config::Input::UP);
                            break;
                        case sf::Keyboard::S:
                            _events.push_back(config::Input::DOWN);
                            break;
                        case sf::Keyboard::Q:
                            _events.push_back(config::Input::LEFT);
                            break;
                        case sf::Keyboard::D:
                            _events.push_back(config::Input::RIGHT);
                            break;
                        case sf::Keyboard::M:
                            _events.push_back(config::Input::MENU);
                            break;
                        case sf::Keyboard::B:
                            _events.push_back(config::Input::PREVGAME);
                            break;
                        case sf::Keyboard::N:
                            _events.push_back(config::Input::NEXTGAME);
                            break;
                        case sf::Keyboard::H:
                            _events.push_back(config::Input::NEXTLIB);
                            break;
                        case sf::Keyboard::J:
                            _events.push_back(config::Input::PREVLIB);
                            break;
                        case sf::Keyboard::Escape:
                            _events.push_back(config::Input::EXIT);
                            break;
                        case sf::Keyboard::Enter:
                            _events.push_back(config::Input::START);
                            break;
                        default:
                            break;
                    }
                }
            }
            return _events;
        }

        void Sfml::setInputEvents() noexcept {
            getInputEvents();
        }
    }
}
