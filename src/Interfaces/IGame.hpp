/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** IGames
*/

#pragma once

#include "Config.hpp"

namespace arcade {
    class IGame {
        public:
            virtual ~IGame() = default;
            virtual const config::ItemList &getItems() noexcept = 0;
            virtual bool doAction(config::Input &) noexcept = 0;
            virtual void manageGameEvents(config::InputList &) noexcept = 0;
            virtual void updateEnvironnement() noexcept = 0;
            virtual int getScore() noexcept = 0;
            virtual bool isGameOver() const noexcept = 0;
            virtual void resetGameOver() noexcept = 0;
            virtual std::string getName() const noexcept = 0;
            virtual int getClockVal() const noexcept = 0;
        protected:
        private:
    };
}
