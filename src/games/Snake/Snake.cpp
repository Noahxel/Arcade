/*
** EPITECH PROJECT, 2023
** snake
** File description:
** arcade
*/

#include "Snake.hpp"

namespace arcade
{
    extern "C" IGame *createIt()
{
        return new game::Snake();
    }
    namespace game
    {
        Snake::Snake()
        {
            std::srand(std::time(nullptr));
            _tailToAdd = 0;
            _isOver = false;
            _clockVal = 20;
            setMap();
        }

        int Snake::getClockVal() const noexcept
        {
            return (_clockVal);
        }

        const config::ItemList &Snake::getItems() noexcept
        {
            _allItems.clear();
            _allItems = _items;
            for (auto i : _snake)
                _allItems.push_back(i);
            return (_allItems);
        }

        void Snake::resetGameOver() noexcept {}

        bool Snake::doAction(config::Input &) noexcept { return true; }

        void Snake::move_snake() noexcept
        {
            int snakesize = _snake.size();
            int slidesSize = _slides.size();

            _directions[0] = _orientation;
            if (_orientation == config::UP)
                _snake[0].y -= _snakeSpeed;
            if (_orientation == config::DOWN)
                _snake[0].y += _snakeSpeed;
            if (_orientation == config::LEFT)
                _snake[0].x -= _snakeSpeed;
            if (_orientation == config::RIGHT)
                _snake[0].x += _snakeSpeed;

            for (int i = 1; i < snakesize; i++) {
                for (int j = 0; j < slidesSize; j++) {
                    if (roundDecimal(_snake[i].y) == _slides[j].y &&
                        roundDecimal(_snake[i].x) == _slides[j].x) {
                        _directions[i] = _slides[j].direction;
                        if (i == snakesize - 1)
                            _slides.erase(_slides.begin());
                    }
                }
                if (_directions[i] == _directions[i - 1] && _directions[i] == config::UP)
                    _snake[i].y = _snake[i - 1].y + 1;
                if (_directions[i] == _directions[i - 1] && _directions[i] == config::DOWN)
                    _snake[i].y = _snake[i - 1].y - 1;
                if (_directions[i] == _directions[i - 1] && _directions[i] == config::LEFT)
                    _snake[i].x = _snake[i - 1].x + 1;
                if (_directions[i] == _directions[i - 1] && _directions[i] == config::RIGHT)
                    _snake[i].x = _snake[i - 1].x - 1;

                if (_directions[i] == config::UP)
                    _snake[i].y -= _snakeSpeed;
                if (_directions[i] == config::DOWN)
                    _snake[i].y += _snakeSpeed;
                if (_directions[i] == config::LEFT)
                    _snake[i].x -= _snakeSpeed;
                if (_directions[i] == config::RIGHT)
                    _snake[i].x += _snakeSpeed;
            }
        }

        float Snake:: roundDecimal(float &nb) noexcept
        {
            return (std::round(nb * 10) / 10);
        }

        void Snake::rotate_snake() noexcept
        {
            config::Input lastInput = _toTurn.back();

            if (lastInput == config::UP || lastInput == config::DOWN) {
                if (std::floor(_snake[0].x) ==  roundDecimal(_snake[0].x) ||
                    std::ceil(_snake[0].x) ==  roundDecimal(_snake[0].x)) {
                    _orientation = lastInput;
                    _slides.push_back({ roundDecimal(_snake[0].x),  roundDecimal(_snake[0].y), lastInput});
                    _toTurn.clear();
                }
            }
            if (lastInput == config::LEFT || lastInput == config::RIGHT) {
                if (std::floor(_snake[0].y) ==  roundDecimal(_snake[0].y) ||
                    std::ceil(_snake[0].y) ==  roundDecimal(_snake[0].y)) {
                    _orientation = lastInput;
                    _slides.push_back({ roundDecimal(_snake[0].x),  roundDecimal(_snake[0].y), lastInput});
                    _toTurn.clear();
                }
            }
        }

        bool Snake::snakeHitThe(std::string &item) noexcept
        {
            for (auto i : _items) {
                if (i.name != item)
                    continue;
                if ((_snake[0].x + 0.1 > i.x && _snake[0].x + 0.1 < i.x + 1 &&
                     _snake[0].y + 0.1 > i.y && _snake[0].y + 0.1 < i.y + 1) ||
                    (_snake[0].x + 0.9 > i.x && _snake[0].x + 0.9 < i.x + 1 &&
                     _snake[0].y + 0.9 > i.y && _snake[0].y + 0.9 < i.y + 1)) {
                    return true;
                }
            }
            return false;
        }

        bool Snake::snakeHitTheSnake() noexcept
        {
            float x = _snake[0].x;
            float y = _snake[0].y;

            if (_directions[0] == config::UP) {
                x += 0.5;
                y += 0.1;
            }
            if (_directions[0] == config::DOWN) {
                x += 0.5;
                y += 0.9;
            }
            if (_directions[0] == config::LEFT) {
                y += 0.5;
                x += 0.1;
            }
            if (_directions[0] == config::RIGHT) {
                x += 0.9;
                y += 0.5;
            }
            for (std::vector<arcade::config::GameItem>::size_type i = 1; i < _snake.size(); i++) {
                if (((x > _snake[i].x && x < _snake[i].x + 1) &&
                     (y > _snake[i].y && y < _snake[i].y + 1)))
                    return (true);
            }
            return (false);
        }


        void Snake::eatAnApple() noexcept
        {
            _tailToAdd += 1;
            for (std::vector<arcade::config::GameItem>::size_type i = 0; i < _items.size(); i++) {
                if (_items[i].name != "apple")
                    continue;
                _items[i].x = getRandVal(1, (_mapLen - 2));
                _items[i].y = getRandVal(1, (_mapHeight - 2));
            }
            _score += 10;
        }


        void Snake::addTail() noexcept
        {
            if (_directions.back() == _directions[_directions.size() - 2] &&
                _directions.back() == _directions[_directions.size() - 3]) {
                float x = roundDecimal(_snake.back().x);
                float y = roundDecimal(_snake.back().y);

                if (_directions.back() == config::UP)
                    y -= 1;
                if (_directions.back() == config::DOWN)
                    y += 1;
                if (_directions.back() == config::LEFT)
                    x -= 1;
                if (_directions.back() == config::RIGHT)
                    x += 1;
                initItem('@', x, y);
                _tailToAdd -= 1;
            }
        }

        void Snake::updateEnvironnement() noexcept
        {
            // auto loop = std::chrono::high_resolution_clock::now();
            std::string wall = "wall";
            std::string apple = "apple";

            if (snakeHitThe(apple))
                eatAnApple();
            if (!_toTurn.empty())
                rotate_snake();
            if (!snakeHitThe(wall) && !snakeHitTheSnake())
                move_snake();
            if (snakeHitThe(wall) || snakeHitTheSnake())
                _isOver = true;
            if (_tailToAdd > 0)
                addTail();
            // auto endLoop = std::chrono::high_resolution_clock::now();
            // std::this_thread::sleep_for(std::chrono::milliseconds(7) - (endLoop - loop));
        }

        int Snake::getScore() noexcept
        {
            return this->_score;
        }

        bool Snake::isGameOver() const noexcept
        {
            return this->_isOver;
        }

        std::string Snake::getName() const noexcept
        {
            return ("Snake");
        }

        void Snake::manageGameEvents(config::InputList &events) noexcept
        {
            for (auto i : events) {
                if ((i == config::UP && _orientation != config::DOWN) ||
                    (i == config::DOWN && _orientation != config::UP) ||
                    (i == config::LEFT && _orientation != config::RIGHT) ||
                    (i == config::RIGHT && _orientation != config::LEFT)) {
                    _toTurn.push_back(i);
                }
            }
        }

        void Snake::initSnake(config::GameItem *item) noexcept
        {
            item->name = "snake";
            item->itemSprite.path = "assets/red_snake.png";
            if (_directions.empty())
                _directions.push_back(config::UP);
            else
                _directions.push_back(_directions.back());
        }

        void Snake::initWall(config::GameItem *item) noexcept
        {
            item->name = "wall";
            item->itemSprite.path = "assets/red_wall.png";
        }

        void Snake::initApple(config::GameItem *item) noexcept
        {
            item->name = "apple";
            item->itemSprite.path = "assets/apple.png";
        }

        void Snake::initItem(char a, int x, int y) noexcept
        {
            config::GameItem item;

            item.x = x;
            item.y = y;
            item.itemSprite.rotation = 0;
            item.itemSprite.ncurses_char = a;
            if (a == '#')
                initWall(&item);
            if (a == '@')
                initSnake(&item);
            if (a == 'a')
                initApple(&item);
            item.itemSprite.name = item.name;
            if (a == '@') {
                _snake.push_back(item);
            } else
                _items.push_back(item);
        }

        int Snake::getRandVal(int start, int end) noexcept
        {
            int val = std::rand() % end + start;

            return (val);
        }

        void Snake::setMap() noexcept
        {
            std::ifstream file;
            std::string line;
            std::string pathToMap = "assets/snake_map.txt";
            std::string snakeElems = "#@a";
            config::Sprite itemSprite;
            int linesize = 0;
            int y = 0;

            file.open(pathToMap);
            for (; std::getline(file, line); y++) {
                linesize = line.length();
                for (int x = 0; x < linesize; x++) {
                    if (snakeElems.find(line[x]) != std::string::npos)
                        initItem(line[x], x, y);
                }
            }
            _mapLen = linesize;
            _mapHeight = y;
            initItem('a', getRandVal(1, _mapLen - 2), getRandVal(1, _mapHeight - 2));
            file.close();
        }
    }
}
