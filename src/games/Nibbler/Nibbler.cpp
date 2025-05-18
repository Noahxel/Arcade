/*
** EPITECH PROJECT, 2023
** Nibbler
** File description:
** arcade
*/

#include "Nibbler.hpp"

namespace arcade
{
    extern "C" IGame *createIt()
{
        return new game::Nibbler();
    }
    namespace game
    {
        Nibbler::Nibbler()
        {
            std::srand(std::time(nullptr));
            _tailToAdd = 0;
            _isStuck = false;
            _isOver = false;
            _clockVal = 20;
            setMap();
        }

        int Nibbler::getClockVal() const noexcept
        {
            return (_clockVal);
        }

        const config::ItemList &Nibbler::getItems() noexcept
        {
            _allItems.clear();
            _allItems = _items;
            for (auto i : _snake)
                _allItems.push_back(i);
            return (_allItems);
        }

        void Nibbler::move_snake() noexcept
        {
            int snakesize = _snake.size();
            int slidesSize = _slides.size();

            _directions[0] = _orientation;
            if (!_isStuck) {
                if (_orientation == config::UP)
                    _snake[0].y -= _snakeSpeed;
                if (_orientation == config::DOWN)
                    _snake[0].y += _snakeSpeed;
                if (_orientation == config::LEFT)
                    _snake[0].x -= _snakeSpeed;
                if (_orientation == config::RIGHT)
                    _snake[0].x += _snakeSpeed;
            }

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

                if (!_isStuck) {
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
        }

        float Nibbler:: roundDecimal(float &nb) noexcept
        {
            return (std::round(nb * 10) / 10);
        }

        void Nibbler::rotate_snake() noexcept
        {
            config::Input lastInput = _toTurn.back();

            if (_isStuck) {
                if (_directions[0] == config::UP)
                    _snake[0].y = std::round(_snake[0].y);
                if (_directions[0] == config::DOWN)
                    _snake[0].y = std::round(_snake[0].y);
                if (_directions[0] == config::LEFT)
                    _snake[0].x = std::round(_snake[0].x);
                if (_directions[0] == config::RIGHT)
                    _snake[0].x = std::round(_snake[0].x);
                _isStuck = false;
            }

            if (lastInput == config::UP || lastInput == config::DOWN) {
                if (std::floor(_snake[0].x) ==  roundDecimal(_snake[0].x) ||
                    std::ceil(_snake[0].x) ==  roundDecimal(_snake[0].x)) {
                    _orientation = lastInput;
                    _slides.push_back({ roundDecimal(_snake[0].x),  roundDecimal(_snake[0].y), lastInput});
                    _toTurn.clear();
                }
            }
            if (lastInput == config::LEFT || lastInput == config::RIGHT) {
                if (std::floor(_snake[0].y) == roundDecimal(_snake[0].y) ||
                    std::ceil(_snake[0].y) == roundDecimal(_snake[0].y)) {
                    _orientation = lastInput;
                    _slides.push_back({ roundDecimal(_snake[0].x),  roundDecimal(_snake[0].y), lastInput});
                    _toTurn.clear();
                }
            }
        }

        bool Nibbler::snakeHitThe(std::string& item) noexcept
        {
            for (const auto& i : _items) {
                if (i.name != item) {
                    continue;
                }
                if ((_snake[0].x + 0.1 > i.x && _snake[0].x + 0.1 < i.x + 1 &&
                     _snake[0].y + 0.1 > i.y && _snake[0].y + 0.1 < i.y + 1) ||
                    (_snake[0].x + 0.9 > i.x && _snake[0].x + 0.9 < i.x + 1 &&
                     _snake[0].y + 0.9 > i.y && _snake[0].y + 0.9 < i.y + 1)) {
                    return true;
                }
            }
            return false;
        }

        bool Nibbler::snakeHitTheSnake() noexcept
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
            for (int i = 1; i < static_cast<int>(_snake.size()); i++) {
                if (((x > _snake[i].x && x < _snake[i].x + 1) &&
                     (y > _snake[i].y && y < _snake[i].y + 1)))
                    return (true);
            }
            return (false);
        }

        void Nibbler::eatAnApple() noexcept
        {
            _tailToAdd += 1;
            for (int i = 1; i < static_cast<int>(_items.size()); i++) {
                if (_items[i].name != "apple") {
                    continue;
                }
                if ((_snake[0].x + 0.1 > _items[i].x && _snake[0].x + 0.1 < _items[i].x + 1 &&
                     _snake[0].y + 0.1 > _items[i].y && _snake[0].y + 0.1 < _items[i].y + 1) ||
                    (_snake[0].x + 0.9 > _items[i].x && _snake[0].x + 0.9 < _items[i].x + 1 &&
                     _snake[0].y + 0.9 > _items[i].y && _snake[0].y + 0.9 < _items[i].y + 1)) {
                    _items.erase(_items.begin() + i);
                }
            }
        }


        void Nibbler::addTail() noexcept
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

        bool Nibbler::isWallAtPos(int x, int y) noexcept
        {
            for (auto elem : _items) {
                if (elem.name != "wall")
                    continue;
                if (elem.x == x && elem.y == y)
                    return (true);
            }
            return (false);
        }

        void Nibbler::isSnakeStuck() noexcept
        {
            int x = std::round(_snake[0].x);
            int y = std::round(_snake[0].y);
            bool isStuck = false;

            if (_directions[0] == config::UP || _directions[0] == config::DOWN) {
                if (!isWallAtPos(x + 1, y) && !isWallAtPos(x - 1, y)) {
                    isStuck = true;
                }
            }
            if (_directions[0] == config::LEFT || _directions[0] == config::RIGHT) {
                if (!isWallAtPos(x, y + 1) && !isWallAtPos(x, y - 1)) {
                    isStuck = true;
                }
            }

            if (!isStuck) {
                if (_directions[0] == config::UP || _directions[0] == config::DOWN) {
                    if (isWallAtPos(x + 1, y) && !isWallAtPos(x - 1, y))
                        _toTurn.push_back(config::LEFT);
                    if (isWallAtPos(x - 1, y) && !isWallAtPos(x + 1, y))
                        _toTurn.push_back(config::RIGHT);
                }
                if (_directions[0] == config::LEFT || _directions[0] == config::RIGHT) {
                    if (isWallAtPos(x, y + 1) && !isWallAtPos(x, y - 1))
                        _toTurn.push_back(config::UP);
                    if (isWallAtPos(x, y - 1) && !isWallAtPos(x, y + 1))
                        _toTurn.push_back(config::DOWN);
                }
            }
            _isStuck = true;
        }

        bool Nibbler::noMoreApple() noexcept
        {
            for (auto i : _items) {
                if (i.name == "apple")
                    return (false);
            }
            _currlevel += 1;
            return (true);
        }

        void Nibbler::resetGameOver() noexcept {}

        bool Nibbler::doAction(config::Input &) noexcept { return true; }

        void Nibbler::updateEnvironnement() noexcept
        {
            // auto loop = std::chrono::high_resolution_clock::now();
            std::string wall = "wall";
            std::string apple = "apple";

            if (_isStuck) {
                if (!_toTurn.empty())
                    rotate_snake();
            } else {
                if (_tailToAdd > 0)
                    addTail();
                if (!_toTurn.empty())
                    rotate_snake();
                if (snakeHitThe(wall))
                    isSnakeStuck();
                if (snakeHitThe(apple))
                    eatAnApple();
                if (!snakeHitTheSnake() && !snakeHitThe(wall))
                    move_snake();
                if (snakeHitTheSnake())
                    _isOver = true;
                if (noMoreApple())
                    setMap();
            }
            // auto endLoop = std::chrono::high_resolution_clock::now();
            // std::this_thread::sleep_for(std::chrono::milliseconds(7) - (endLoop - loop));
        }

        int Nibbler::getScore() noexcept
        {
            return this->_currlevel;
        }

        bool Nibbler::isGameOver() const noexcept
        {
            return this->_isOver;
        }

        std::string Nibbler::getName() const noexcept
        {
            return ("Nibbler");
        }

        void Nibbler::manageGameEvents(config::InputList& events) noexcept {
            for (auto i : events) {
                if ((i == config::UP && _orientation != config::DOWN) ||
                    (i == config::DOWN && _orientation != config::UP) ||
                    (i == config::LEFT && _orientation != config::RIGHT) ||
                    (i == config::RIGHT && _orientation != config::LEFT)) {
                    _toTurn.push_back(i);
                }
            }
        }

        void Nibbler::initSnake(config::GameItem *item) noexcept
        {
            item->name = "snake";
            item->itemSprite.path = "assets/red_snake.png";
            if (_directions.empty())
                _directions.push_back(config::UP);
            else
                _directions.push_back(_directions.back());
        }

        void Nibbler::initWall(config::GameItem *item) noexcept
        {
            item->name = "wall";
            item->itemSprite.path = "assets/red_wall.png";
        }

        void Nibbler::initApple(config::GameItem *item) noexcept
        {
            item->name = "apple";
            item->itemSprite.path = "assets/apple.png";
        }

        void Nibbler::initItem(char a, int x, int y) noexcept
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

        int Nibbler::getRandVal(int start, int end) noexcept
        {
            int val = std::rand() % end + start;

            return (val);
        }

        void Nibbler::setMap() noexcept
        {
            std::ifstream file;
            std::string line;
            std::string pathToMap = "assets/nibbler_" + std::to_string(_currlevel) + ".txt";
            std::string snakeElems = "#@a";
            config::Sprite itemSprite;
            int linesize = 0;
            int y = 0;

            _mapLen = 0;
            _mapHeight = 0;
            _orientation = config::UP;
            _snake.clear();
            _toTurn.clear();
            _directions.clear();
            _slides.clear();
            _items.clear();

            file.open(pathToMap);
            if (!file.is_open()) {
                pathToMap = "assets/snake_map.txt";
                file.open(pathToMap);
            }
            for (; std::getline(file, line); y++) {
                linesize = line.length();
                for (int x = 0; x < linesize; x++) {
                    if (snakeElems.find(line[x]) != std::string::npos)
                        initItem(line[x], x, y);
                }
            }
            _mapLen = linesize;
            _mapHeight = y;
            if (pathToMap == "assets/snake_map.txt")
                initItem('a', getRandVal(1, _mapLen - 2), getRandVal(1, _mapHeight - 2));
            file.close();
        }
    }
}
