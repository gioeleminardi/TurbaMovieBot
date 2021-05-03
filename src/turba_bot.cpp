/**
 * \file       turba_bot.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#include "turba_bot.hpp"

turba_bot::turba_bot(const std::string &token) : _bot(std::make_unique<TgBot::Bot>(token)) {

}

turba_bot::~turba_bot() = default;