/**
 * \file       controller.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#ifndef TURBAMOVIEBOT_CONTROLLER_HPP
#define TURBAMOVIEBOT_CONTROLLER_HPP

#include <tgbot/types/Message.h>

#include "icontroller.hpp"
class controller : public icontroller {
public:
    void add_movie(const TgBot::Message::Ptr& msg) override;
    void delete_movie(const TgBot::Message::Ptr& msg) override;
    std::string extract_movie(const TgBot::Message::Ptr& msg) override;
    void my_movies(const TgBot::Message::Ptr& msg) override;
    void all_movies(const TgBot::Message::Ptr& msg) override;
    void done_watch(const TgBot::Message::Ptr& msg) override;
};

#endif  // TURBAMOVIEBOT_CONTROLLER_HPP
