/**
 * \file       controller.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#include "controller.hpp"

#include <tgbot/tools/StringTools.h>

#include <iostream>
#include <regex>

#include "model/movie.hpp"
#include "utils.hpp"

controller::controller() = default;

controller::~controller() = default;

status controller::add_movie(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return status::not_a_group;
    }

    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    auto msg_str = msg->text;

    std::regex newlines_re("\n+");
    msg_str = std::regex_replace(msg_str, newlines_re, " ");

    auto msg_tokens = StringTools::split(msg_str, ' ');

    if (msg_tokens.size() < 2) {
        return status::malformed_cmd;
    }

    std::string movie_title;
    std::string movie_url;

    for (const auto& token : msg_tokens) {
        if (token.empty() || StringTools::startsWith(token, "/"))
            continue;

        if (StringTools::startsWith(token, "http")) {
            movie_url = token;
        } else {
            movie_title.append(token).append(" ");
        }
    }

    rtrim(movie_title);

    try {
        _db_handler.save_movie(model::movie{-1, user_id, group_id, movie_title, movie_url, std::time(nullptr), model::movie_status::idle});
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

std::vector<model::movie> controller::extract_movie(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return {};
    }

    auto group_id = msg->chat->id;

    return _db_handler.extract_movie(group_id);
}

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

status controller::done_watch(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return status::not_a_group;
    }
    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    auto ret = _db_handler.done_watch(user_id, group_id);
    if (ret == -1) {
        return status::error;
    } else if (ret == -2) {
        return status::not_allowed;
    }

    return status::ok;
}

void controller::init() { _db_handler.init_schema(); }

status controller::swap_movies(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return status::not_a_group;
    }

    auto tokens = StringTools::split(msg->text, ' ');
    if (tokens.size() != 3) {
        return status::malformed_cmd;
    }

    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    int movie_id1;
    int movie_id2;

    try {
        movie_id1 = std::stoi(tokens[1]);
        movie_id2 = std::stoi(tokens[2]);
    } catch (std::invalid_argument& e) {
        return status::malformed_cmd;
    }

    auto ret = _db_handler.swap_movies(user_id, group_id, movie_id1, movie_id2);

    if (ret != 0) {
        return status::error;
    }

    return status::ok;
}
