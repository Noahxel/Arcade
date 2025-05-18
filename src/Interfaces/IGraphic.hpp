/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IGraphical
*/

#pragma once

#include "Config.hpp"

namespace arcade {
    class IGraphic {
        public:
            virtual ~IGraphic() = default;
            virtual void initWindow(const int &, const int &, const std::string &) noexcept = 0;
            virtual void clearWindow() const noexcept = 0;
            virtual void updateWindow() noexcept = 0;
            virtual void drawText(const std::string &, int, int, bool) noexcept = 0;
            virtual void drawItem(const config::GameItem &) noexcept = 0;
            virtual void setInputEvents() noexcept = 0;
            virtual config::InputList getInputEvents() noexcept = 0;
            virtual std::string getName() const noexcept = 0;
        protected:
        private:
    };
}
