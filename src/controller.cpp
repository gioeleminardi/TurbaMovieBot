/**
 * \file       controller.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#include "controller.hpp"

#include <tgbot/tools/StringTools.h>

#include <iostream>

#include "model/movie.hpp"

controller::controller() = default;

controller::~controller() = default;

status controller::add_movie(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return status::not_a_group;
    }

    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    std::string movie_url;

    auto msg_tokens = StringTools::split(msg->text, ' ');

    if (msg_tokens.size() < 2) {
        //        return std::string("Utilizzo: /aggiungi <titolo film> [http(s)://<url>]");
        return status::malformed_cmd;
    }

    auto movie_title = msg_tokens[1];

    for (auto i = 2; i < msg_tokens.size(); ++i) {
        auto token = msg_tokens[i];
        if (!StringTools::startsWith(token, "http")) {
            movie_title.append(" ").append(token);
        } else {
            movie_url = token;
        }
    }

    try {
        _db_handler.save_movie(model::movie{-1, user_id, group_id, movie_title, movie_url, std::time(nullptr), false});
    } catch (const std::system_error& e) {
        if (StringTools::startsWith(e.what(), "UNIQUE")) {
            return status::already_saved;
        } else {
            return status::error;
        }
    }
    return status::ok;
}

status controller::delete_movie(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return status::not_a_group;
    }

    auto tokens = StringTools::split(msg->text, ' ');
    if (tokens.size() != 2) {
        return status::malformed_cmd;
    }
    int movie_id;

    try {
        movie_id = std::stoi(tokens[1]);
    } catch (std::invalid_argument& e) {
        return status::malformed_cmd;
    }

    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    if (_db_handler.delete_user_movie(user_id, group_id, movie_id) < 0) {
        return status::not_found;
    }

    return status::ok;
}

std::string controller::extract_movie(const TgBot::Message::Ptr& msg) { return ("extract_movie\n"); }

std::vector<model::movie> controller::my_movies(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return {};
    }

    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    return _db_handler.get_user_movies(user_id, group_id);
}

std::unordered_map<std::int32_t, std::vector<model::movie>> controller::all_movies(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return std::unordered_map<std::int32_t, std::vector<model::movie>>();
    }

    auto group_id = msg->chat->id;

    return _db_handler.get_group_movies(group_id);
}

status controller::done_watch(const TgBot::Message::Ptr& msg) { return status::error; }

void controller::init() { _db_handler.init_schema(); }
