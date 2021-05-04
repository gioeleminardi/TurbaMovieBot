/**
 * \file       main.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */

#include <iostream>

#include "bot.hpp"

int main() {
    std::string token = getenv("TOKEN");
    std::cout << "Token: " << token << std::endl;

    bot turbaBot(token);

    turbaBot.init();

    turbaBot.run();

    return 0;
}