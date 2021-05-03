/**
 * \file       turba_bot.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#ifndef TURBAMOVIEBOT_TURBA_BOT_HPP
#define TURBAMOVIEBOT_TURBA_BOT_HPP

#include <string>
#include <tgbot/tgbot.h>
#include "turba_commands.hpp"
#include <map>

namespace turba_ns = turba_v1;

class turba_bot {
public:
    explicit turba_bot(const std::string &token);

    ~turba_bot();

    void init();

    void run();

    void command_handler(const TgBot::Message::Ptr &msg);
private:
    TgBot::Bot _bot;
    TgBot::TgLongPoll _long_poll;
};

#endif //TURBAMOVIEBOT_TURBA_BOT_HPP
