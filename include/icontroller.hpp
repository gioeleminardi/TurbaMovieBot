//
// Created by varkrid on 5/3/21.
//

#ifndef TURBAMOVIEBOT_ICONTROLLER_HPP
#define TURBAMOVIEBOT_ICONTROLLER_HPP

#include <string>

class icontroller {
public:
    using Ptr = std::unique_ptr<icontroller>;

    virtual void add_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual void delete_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual std::string extract_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual void my_movies(const TgBot::Message::Ptr& msg) = 0;
    virtual void all_movies(const TgBot::Message::Ptr& msg) = 0;
    virtual void done_watch(const TgBot::Message::Ptr& msg) = 0;
};

#endif  // TURBAMOVIEBOT_ICONTROLLER_HPP
