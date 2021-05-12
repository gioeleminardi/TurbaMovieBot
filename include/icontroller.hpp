//
// Created by varkrid on 5/3/21.
//

#ifndef TURBAMOVIEBOT_ICONTROLLER_HPP
#define TURBAMOVIEBOT_ICONTROLLER_HPP

#include <model/movie.hpp>
#include <string>

enum class status { ok, error, already_saved, not_found, not_a_group, malformed_cmd, not_allowed };

class icontroller {
public:
    using Ptr = std::unique_ptr<icontroller>;

    virtual void init() = 0;
    virtual status add_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual status delete_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual std::vector<model::movie> extract_movie(const TgBot::Message::Ptr& msg) = 0;
    virtual std::vector<model::movie> my_movies(const TgBot::Message::Ptr& msg) = 0;
    virtual std::unordered_map<std::int32_t, std::vector<model::movie>> all_movies(const TgBot::Message::Ptr& msg) = 0;
    virtual status done_watch(const TgBot::Message::Ptr& msg) = 0;
    virtual status swap_movies(const TgBot::Message::Ptr& msg) = 0;
};

#endif  // TURBAMOVIEBOT_ICONTROLLER_HPP
