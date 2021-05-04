/**
 * \file       controller.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_CONTROLLER_HPP
#define TURBAMOVIEBOT_CONTROLLER_HPP

#include <tgbot/tgbot.h>

#include "db_handler.hpp"
#include "icontroller.hpp"

class controller : public icontroller {
public:
    controller();
    ~controller();
    void init() override;
    std::string add_movie(const TgBot::Message::Ptr& msg) override;
    std::string delete_movie(const TgBot::Message::Ptr& msg) override;
    std::string extract_movie(const TgBot::Message::Ptr& msg) override;
    std::string my_movies(const TgBot::Message::Ptr& msg) override;
    std::unordered_map<std::int32_t, std::vector<model::movie>> all_movies(const TgBot::Message::Ptr& msg) override;
    std::string done_watch(const TgBot::Message::Ptr& msg) override;

private:
    db_handler _db_handler;
};

#endif  // TURBAMOVIEBOT_CONTROLLER_HPP
