/**
 * \file       bot.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#ifndef TURBAMOVIEBOT_BOT_HPP
#define TURBAMOVIEBOT_BOT_HPP

#include <tgbot/tgbot.h>

#include <icontroller.hpp>
#include <map>
#include <string>

#include "commands.hpp"

class bot {
public:
    explicit bot(const std::string& token);

    ~bot();

    void init();

    void run();

private:
    void load_commands();

private:
    TgBot::Bot _bot;
    TgBot::TgLongPoll _long_poll;
    std::vector<turba_bot::command> _commands;
    icontroller::Ptr _controller;
};

#endif  // TURBAMOVIEBOT_BOT_HPP
