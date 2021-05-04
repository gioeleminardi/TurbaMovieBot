//
// Created by varkrid on 5/3/21.
//

#ifndef TURBAMOVIEBOT_ICONTROLLER_HPP
#define TURBAMOVIEBOT_ICONTROLLER_HPP

#include <model/movie.hpp>
#include <string>

class icontroller {
public:
    using Ptr = std::unique_ptr<icontroller>;

    virtual void init() = 0;
    virtual std::string add_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual std::string delete_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual std::string extract_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual std::string my_movies(const TgBot::Message::Ptr& msg) = 0;
    virtual std::unordered_map<std::int32_t, std::vector<model::movie>> all_movies(const TgBot::Message::Ptr& msg) = 0;
    virtual std::string done_watch(const TgBot::Message::Ptr& msg) = 0;
};

#endif  // TURBAMOVIEBOT_ICONTROLLER_HPP
