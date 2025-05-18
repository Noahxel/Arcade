/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** DynamicLoader
*/

#pragma once

#include <stdexcept>
#include <dlfcn.h>
#include <memory>
#include <string>

namespace arcade {
    template <typename T>
    class DynamicLoader {
        public:
            using creator_ptr = T *(*)(bool o);
            DynamicLoader() {}

            ~DynamicLoader()
            {
                if (_libp != nullptr) {
                    dlclose(_libp);
                    _libp = nullptr;
                }
            }

            std::unique_ptr<T> loadPlugin(std::string path, bool open_window = true)
            {
                if (_libp != nullptr) {
                    dlclose(_libp);
                    _libp = nullptr;
                }
                if (!(_libp = dlopen(path.c_str(), RTLD_LAZY)))
                    throw std::runtime_error("dlopen failed: " + std::string(dlerror()));
                _creator = reinterpret_cast<creator_ptr>(dlsym(_libp, "createIt"));
                if (!_creator)
                    throw std::runtime_error("dynload: can't create instance");
                return std::unique_ptr<T>(_creator(open_window));
            }

            void *getSym(std::string sym)
            {
                void *ret = nullptr;

                if (_libp) {
                    ret = dlsym(_libp, sym.c_str());
                }
                return (ret);
            }

        private:
            creator_ptr _creator = nullptr;
            void *_libp = nullptr;
    };
}
