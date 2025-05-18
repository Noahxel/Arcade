/*
** EPITECH PROJECT, 2023
** Ncurse
** File description:
** arcade
*/

#include "Ncurses.hpp"

namespace arcade
{
    extern "C" IGraphic *createIt(bool o) {
        return new graphic::Ncurses(o);
    }
    namespace graphic
    {
        Ncurses::Ncurses(bool open)
        {
            if (open)
                initWindow(config::ScreenHeight, config::ScreenWidth, "ARCADE");
        }

        Ncurses::~Ncurses()
        {
            endwin();
        }

        void Ncurses::initWindow(const int &width, const int &height, const std::string &title) noexcept
        {
            (void)width;
            (void)height;
            (void)title;
            SCREEN *screen = newterm(NULL, stdout, stdin);
            if (screen)
                _window = stdscr;
            else
                _window = nullptr;
            start_color();
            noecho();
            curs_set(0);
            init_pair(0, COLOR_BLACK, COLOR_BLACK);
            init_pair(1, COLOR_RED, COLOR_BLACK);
            init_pair(2, COLOR_BLUE, COLOR_BLUE);
            init_pair(3, COLOR_GREEN, COLOR_BLACK);
            init_pair(4, COLOR_YELLOW, COLOR_BLACK);
            init_pair(5, COLOR_CYAN, COLOR_BLACK);
            init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
            nodelay(this->_window, true);
        }

        void Ncurses::clearWindow() const noexcept
        {
            werase(this->_window);
        }

        void Ncurses::updateWindow() noexcept {
            wrefresh(this->_window);
        }

        void Ncurses::drawText(const std::string &str, int x, int y, bool center) noexcept
        {
            int startX = center ? (getmaxx(this->_window) - str.length()) / 2 : x;
            mvwprintw(this->_window, y, startX, "%s", str.c_str());
        }

        void Ncurses::drawItem(const config::GameItem &item) noexcept
        {
            attron(COLOR_PAIR(static_cast<int>(item.itemSprite.color) + 1));
            mvwprintw(this->_window, item.y, item.x, "%c", static_cast<uint32_t>(item.itemSprite.ncurses_char));
            attroff(COLOR_PAIR(static_cast<int>(item.itemSprite.color) + 1));
        }

        std::string Ncurses::getName() const noexcept {
            return "NCURSES";
        }

        void Ncurses::setInputEvents() noexcept
        {
            keypad(stdscr, TRUE);
        }

        config::InputList Ncurses::getInputEvents() noexcept {
            int input = getch();

            _inputList.clear();
            switch (input) {
                case 'z':
                    _inputList.push_back(config::Input::UP);
                    break;
                case 's':
                    _inputList.push_back(config::Input::DOWN);
                    break;
                case 'q':
                    _inputList.push_back(config::Input::LEFT);
                    break;
                case 'd':
                    _inputList.push_back(config::Input::RIGHT);
                    break;
                case 'm':
                    _inputList.push_back(config::Input::MENU);
                    break;
                case 'b':
                    _inputList.push_back(config::Input::PREVGAME);
                    break;
                case 'n':
                    _inputList.push_back(config::Input::NEXTGAME);
                    break;
                case 'h':
                    _inputList.push_back(config::Input::NEXTLIB);
                    break;
                case 'j':
                    _inputList.push_back(config::Input::PREVLIB);
                    break;
                case 27:
                    _inputList.push_back(config::Input::EXIT);
                    break;
                case 10:
                    _inputList.push_back(config::Input::START);
                    break;
                default:
                    break;
            }
            return _inputList;
        }
    }
}
