/**
 * \file       turba_bot.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#ifndef TURBAMOVIEBOT_TURBA_BOT_HPP
#define TURBAMOVIEBOT_TURBA_BOT_HPP

#include <string>
#include <tgbot/tgbot.h>

class turba_bot {
    using bot_ptr = std::unique_ptr<TgBot::Bot>;

public:
    explicit turba_bot(const std::string& token);
    ~turba_bot();

private:
    bot_ptr _bot;
};

#endif //TURBAMOVIEBOT_TURBA_BOT_HPP
