/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Snake
*/

#pragma once

#include <memory>
#include <thread>
#include <fstream>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include "IGame.hpp"

extern "C" __attribute__((visibility("default"))) const char gameflag[] = "game";
#define  spriteSize 16

namespace arcade {
    extern "C" IGame* createIt();
    namespace game {
        class Snake : public IGame {
            public:
                Snake();
                const config::ItemList &getItems() noexcept;
                void updateEnvironnement() noexcept;
                void resetGameOver() noexcept;
                bool doAction(config::Input &) noexcept;
                int getScore() noexcept;
                bool isGameOver() const noexcept;
                std::string getName() const noexcept;
                void setMap() noexcept;
                void manageGameEvents(config::InputList &events) noexcept;
                void rotateSnake(config::Input direction) noexcept;
                void move_snake() noexcept;
                void eatAnApple() noexcept;
                void rotate_snake() noexcept;
                float roundDecimal(float &) noexcept;
                bool snakeHitThe(std::string &) noexcept;
                bool snakeHitTheSnake() noexcept;
                void initSnake(config::GameItem *item) noexcept;
                void initWall(config::GameItem *item) noexcept;
                void initApple(config::GameItem *item) noexcept;
                void initItem(char a, int x, int y) noexcept;
                int getRandVal(int start, int end) noexcept;
                void addTail() noexcept;
                int getClockVal() const noexcept;

            protected:
            private:
                typedef struct slides_s {
                    float x;
                    float y;
                    config::Input direction;
                } slides_t;

                config::ItemList _items;
                config::ItemList _snake;
                config::ItemList _allItems;
                int _score = 0;
                bool _isOver = false;
                config::Input _orientation = config::UP;
                float _snakeSpeed = 0.1;
                std::vector<slides_t> _slides;
                std::vector<config::Input> _directions;
                std::vector<config::Input> _toTurn;
                int _mapLen;
                int _mapHeight;
                int _tailToAdd;
                int _clockVal;
        };
    }
}
