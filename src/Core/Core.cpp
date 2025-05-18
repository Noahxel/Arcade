/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Core
*/

#include "Core.hpp"

namespace arcade
{
    void Core::getValidLibsNames()
    {
        for (auto i : std::filesystem::directory_iterator("lib/"))
        {
            if (i.path().extension() != ".so")
                continue;
            _gameloader.loadPlugin(i.path(), false);
            std::string filename = i.path();
            std::string filepath = i.path();
            size_t extensionPos = filename.find_last_of(".");
            filename.erase(extensionPos);
            filename.erase(0, 11);
            if (_gameloader.getSym("gameflag") != NULL)
                _games_infos.push_back((lib_infos_t){filename, filepath});
            if (_gameloader.getSym("graphicflag") != NULL)
                _graphics_infos.push_back((lib_infos_t){filename, filepath});
        }
    }

    Core::Core([[maybe_unused]]std::string selected_lib)
    {
        _gameloader = DynamicLoader<IGame>();
        _graphicloader = DynamicLoader<IGraphic>();
        getValidLibsNames();
        _curr_graphics = nullptr;
        _curr_game = nullptr;
        terminal_menu();
    }

    Core::~Core()
    {
    }

    lib_infos_t Core::menu_step(std::vector <lib_infos_t> elem, std::string &type)
    {
        std::string input = "";
        int index;

        for (int i = 1; i < static_cast<int>(elem.size()) + 1; i++)
            printf("press %d to chose: %s\n", i, elem[i - 1].lib_name.c_str());
        std::cin >> input;
        if ((index = atoi(input.c_str())) <= 0 || (index - 1) >= static_cast<int>(elem.size())) {
            printf("Wrong input\n");
            return (menu_step(elem, type));
        }
        if (type == "graphics")
            _graphicIndex = index - 1;
        if (type == "games")
            _gameIndex = index - 1;
        return elem.at(index - 1);
    }

    std::string Core::getUsername()
    {
        std::string input = "";

        std::getline(std::cin, input);
        while (input.find(' ') != std::string::npos)
        {
            printf("Incorrect username, retry with no space:\n");
            std::getline(std::cin, input);
        }
        if (input.length() == 0)
            return ("Anonymous");
        return input;
    }

    void Core::printScore()
    {
        for (uint i = 0; i < _games_infos.size(); i++) {
            std::string temp = pathToScores;
            std::string path = temp + _games_infos[i].lib_name + ".txt";
            std::ifstream fs(path.c_str());
            std::string myline;
            int count = 0;
            if (fs.is_open()) {
                while (fs and count < 3) {
                    std::getline(fs, myline);
                    if (myline.length() > 0) {
                        if (count == 0) {
                            printf("\nBest scores in %s:\n\n", _games_infos[i].lib_name.c_str());
                            printf("\tUSER\tSCORE\n\n");
                        }
                        int end = myline.find(' ');
                        printf("%d.\t%s\t%s\n", count + 1, myline.substr(0, end).c_str(), myline.substr(end + 1, myline.length()).c_str());
                        count++;
                    }
                }
            }
            fs.close();
        }
        printScoreByName();
    }

    void Core::printScoreByName()
    {
        if (_username == "Anonymous") {
            for (uint i = 0; i < _games_infos.size(); i++) {
                std::string temp = pathToScores;
                std::string path = temp + _games_infos[i].lib_name + ".txt";
                std::ifstream fs(path.c_str());
                std::string myline;
                int count = 0;
                if (fs.is_open()) {
                    while (fs and count < 3) {
                        std::getline(fs, myline);
                        if (myline.length() > 0 && myline.substr(0, myline.find(' ')) == _username) {
                            if (count == 0) {
                                printf("\nYour best scores in %s:\n\n", _games_infos[i].lib_name.c_str());
                                printf("\tSCORE\n\n");
                            }
                            int end = myline.find(' ');
                            printf("%d.\t%s\n", count + 1, myline.substr(end + 1, myline.length()).c_str());
                            count++;
                        }
                    }
                }
                fs.close();
            }
        }
    }

    void Core::saveScore()
    {
        if (_curr_game->getScore() > 0)
        {
            bool isScoreSaved = false;
            std::string temp = pathToScores;
            std::string path = temp + _selected_game.lib_name + ".txt";

            if (!std::filesystem::exists(path)) {
                std::ofstream createfile(path);
                createfile.close();
            }

            std::ifstream fs(path.c_str());
            std::ofstream newfs(path + "2");
            std::string myline;
            if (fs.is_open())
            {
                while (fs)
                {
                    std::getline(fs, myline);
                    if (myline.length() > 0)
                    {
                        int end = myline.find(' ');
                        if (std::stoi(myline.substr(end + 1, myline.length())) < _curr_game->getScore() && !isScoreSaved)
                        {
                            newfs << _username << ' ' << _curr_game->getScore() << std::endl;
                            isScoreSaved = true;
                        }
                        newfs << myline << std::endl;
                    } else if (!isScoreSaved) {
                        newfs << _username << ' ' << _curr_game->getScore() << std::endl;
                        break;
                    }
                }
            }
            fs.close();
            newfs.close();
            rename((path + "2").c_str(), path.c_str());
            std::remove((path + "2").c_str());
        }
    }

    void Core::terminal_menu()
    {
        std::string input;
        std::string gamesStr = "games";
        std::string graphicsStr = "graphics";

        std::cout << ("ARCADE:") << std::endl;
        std::cout << ("enter your name (enter nothing to play anonymously, no space allowed):") << std::endl;
        _username = getUsername();
        printScore();
        std::cout << ("\npick a game:") << std::endl;
        _selected_game = menu_step(_games_infos, gamesStr);
        std::cout << ("\npick graphicals") << std::endl;
        _selected_graphics = menu_step(_graphics_infos, graphicsStr);
        // TO DO: validation step
        _curr_game = _gameloader.loadPlugin(_selected_game.lib_path, false);
        _curr_graphics = _graphicloader.loadPlugin(_selected_graphics.lib_path);
    }

    void Core::nextLib()
    {
        _graphicIndex++;
        if (_graphicIndex == static_cast<int>(_graphics_infos.size()))
            _graphicIndex = 0;
        if (_curr_graphics)
            _curr_graphics.reset();
        _curr_graphics = _graphicloader.loadPlugin(_graphics_infos[_graphicIndex].lib_path);
    }

    void Core::prevLib()
    {
        _graphicIndex--;
        if (_graphicIndex < 0)
            _graphicIndex = _graphics_infos.size() - 1;
        if (_curr_graphics)
            _curr_graphics.reset();
        _curr_graphics = _graphicloader.loadPlugin(_graphics_infos[_graphicIndex].lib_path);
    }

    void Core::nextGame()
    {
        _gameIndex++;
        if (_gameIndex == static_cast<int>(_games_infos.size()))
            _gameIndex = 0;
        if (_curr_game)
            _curr_game.reset();
        _curr_game = _gameloader.loadPlugin(_games_infos[_gameIndex].lib_path);
    }

    void Core::prevGame()
    {
        _gameIndex--;
        if (_gameIndex < 0)
            _gameIndex = _games_infos.size() - 1;
        if (_curr_game)
            _curr_game.reset();
        _curr_game = _gameloader.loadPlugin(_games_infos[_gameIndex].lib_path);
    }

    void Core::resetGame()
    {
        prevGame();
        nextGame();
        run();
    }

    void Core::goToMenu()
    {
        _curr_game.reset();
        _curr_graphics.reset();
        terminal_menu();
        run();
    }

    void Core::exitProperly()
    {
        _curr_game.reset();
        _curr_graphics.reset();
        exit(0);
    }

    bool Core::manageGameOverEvents(config::InputList &events)
    {
        for (auto i : events) {
            switch (i) {
            case (config::EXIT):
                exitProperly();
                return (false);
            case (config::MENU):
                goToMenu();
                break;
            case (config::START):
                resetGame();
                break;
            default:
                break;
            }
        }
        return (true);
    }

    bool Core::manageOutGameEvents(config::InputList &events)
    {
        for (auto i : events) {
            switch (i) {
            case (config::NEXTLIB):
                nextLib();
                break;
            case (config::PREVLIB):
                prevLib();
                break;
            case (config::NEXTGAME):
                nextGame();
                break;
            case (config::PREVGAME):
                prevGame();
                break;
            case (config::EXIT):
                return (false);
                break;
            case (config::MENU):
                goToMenu();
                break;
            case (config::START):
                resetGame();
                break;
            default:
                break;
            }
        }
        return (true);
    }

    void Core::drawGameOver()
    {
        config::InputList events;

        saveScore();
        while (manageGameOverEvents(events = _curr_graphics->getInputEvents())) {
            _curr_graphics->clearWindow();
            _curr_graphics->drawText("GAME OVER", 0, 13, true);
            _curr_graphics->drawText("Your Score: " + std::to_string(_curr_game->getScore()), 0, 15, true);
            _curr_graphics->drawText("ESCAPE -> Exit", 0, 17, true);
            _curr_graphics->drawText("Enter -> Play Again", 0, 19, true);
            _curr_graphics->drawText("M -> Back to Menu", 0, 18, true);
            _curr_graphics->updateWindow();
        }
    }

    void Core::drawInfos()
    {
        _lineOfDisplay = 1;
        _curr_graphics->drawText("PLAYER: " + _username, _lineOfDisplay, 0, false);
        _curr_graphics->drawText(_curr_game->getName(), _lineOfDisplay += 13, 0, false);
        _curr_graphics->drawText("SCORE: " + std::to_string(_curr_game->getScore()), _lineOfDisplay += 13, 0, false);
    }

    void Core::wait(const std::chrono::high_resolution_clock::time_point &loop) const noexcept
    {
        auto endLoop = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(_curr_game->getClockVal()) - (endLoop - loop));
    }

    void Core::run()
    {
        config::ItemList items;
        config::InputList events;

        while (manageOutGameEvents(events = _curr_graphics->getInputEvents())) {
            auto loop = std::chrono::high_resolution_clock::now();
            _curr_game->manageGameEvents(events);
            _curr_graphics->clearWindow();
            items = _curr_game->getItems();
            for (auto i : items)
                _curr_graphics->drawItem(i);
            drawInfos();
            _curr_graphics->updateWindow();
            _curr_game->updateEnvironnement();
            if (_curr_game->isGameOver()) {
                drawGameOver();
            }
            wait(loop);
        }
    }
}
