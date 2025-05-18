/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Config
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>

namespace arcade
{
    namespace config
    {
        enum Input
        {
            UP,
            LEFT,
            DOWN,
            RIGHT,
            START,
            NEXTLIB,
            PREVLIB,
            NEXTGAME,
            PREVGAME,
            MENU,
            EXIT,
        };
        using InputList = std::vector<Input>;

        enum Color
        {
            BLUE,
            RED,
        };

        struct Sprite
        {
            int rotation;
            char ncurses_char;
            std::string name;
            std::string path;
            Color color;
            Color background;
        };

        struct GameItem
        {
            std::string name;
            Sprite itemSprite;
            float x;
            float y;
        };
        using ItemList = std::vector<GameItem>;

        constexpr int ScreenWidth = 1000;
        constexpr int ScreenHeight = 1000;
    }
}
