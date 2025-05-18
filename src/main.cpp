/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Main
*/

#include "Core.hpp"
#include <cstring>

int help()
{
    printf("./arcade [default_graphic_lib.so]\n\nAvailable graphic libraries:\n\t- Ncurses\n\t- Sfml\n\t- SDL2\n\nAvailable games:\n\t- Pacman\n\t- Snake\n\n");
    return (1);
}

int handle_error (int argc, char **argv)
{
    void *libptr;

    if (argc != 2) {
        std::cout << "Wrong argument, retry with -h." << std::endl;
        return (84);
    }

    if (strcmp(argv[1], "-h") == 0) {
        return help();
    }

    std::string libPath = argv[1];

    if (!(std::filesystem::exists(libPath))) {
        std::cout << argv[1] << " not found" << std::endl;
        return (84);
    }

    if (!(libptr = dlopen(argv[1], RTLD_LAZY))) {
        std::cout << "Failed to load library: " << dlerror() << std::endl;
        return (84);
    }

    if (libptr != NULL) {
        if (dlclose(libptr) < 0) {
            std::cout << "Failed to close library: " << dlerror() << std::endl;
            return (84);
        }
    }

    return (0);
}

int main(int argc, char **argv)
{
    int he = handle_error(argc, argv);
    if (he == 84)
        return (84);
    if (he == 1)
        return (0);
    arcade::Core *core = new arcade::Core(argv[1]);
    core->run();
    return (0);
}
