/**
 * \file       bot.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#ifndef TURBAMOVIEBOT_BOT_HPP
#define TURBAMOVIEBOT_BOT_HPP

#include <string>
#include <tgbot/tgbot.h>
#include "commands.hpp"
#include <map>
#include <icommander.hpp>

class bot : public icommander {
public:
    explicit bot(const std::string &token);

    ~bot();

    void init();

    void run();

private:
    void parse_cmd(const TgBot::Message::Ptr &msg);

    void add_movie(std::string title, std::string resource_url) override;

    void delete_movie(std::string title) override;

    std::string extract_movie() override;

    void my_movies() override;

    void all_movies() override;

private:
    TgBot::Bot _bot;
    TgBot::TgLongPoll _long_poll;
};

#endif //TURBAMOVIEBOT_BOT_HPP
