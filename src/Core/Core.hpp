/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core
*/

#pragma once
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <thread>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include "IGame.hpp"
#include "IGraphic.hpp"
#include "DynamicLoader.hpp"

static const std::string PathToGraphical = "src/graphics/";
static const std::string pathToGames = "src/games/";
static const std::string pathToScores = "src/Scores/";

typedef struct lib_infos_s {
    std::string lib_name;
    std::string lib_path;
} lib_infos_t;

namespace arcade {
    class Core {
        public:
            Core(std::string selected_lib);
            ~Core();
            void run();

        protected:
        private:
            void getValidLibsNames();
            bool manageOutGameEvents(config::InputList &);
            void nextLib();
            void prevLib();
            void nextGame();
            void prevGame();
            std::string getUsername();
            void printScore();
            void printScoreByName();
            void saveScore();
            void drawInfos();
            void resetGame();
            void drawInfoGame() noexcept;
            void drawGameOver();
            void goToMenu();
            void exitProperly();
            void terminal_menu();
            bool manageGameOverEvents(config::InputList &events);
            void wait(const std::chrono::high_resolution_clock::time_point &loop) const noexcept;
            lib_infos_t menu_step(std::vector <lib_infos_t> elem, std::string &);
            std::string _current_lib;
            lib_infos_t _selected_game;
            lib_infos_t _selected_graphics;
            std::vector <lib_infos_t> _games_infos;
            std::vector <lib_infos_t> _graphics_infos;
            std::unique_ptr <IGraphic> _curr_graphics;
            std::unique_ptr <IGame> _curr_game;
            DynamicLoader<IGame> _gameloader;
            DynamicLoader<IGraphic> _graphicloader;
            int _graphicIndex;
            int _gameIndex;
            int _input;
            std::string _username;
            int _lineOfDisplay;
    };
}
