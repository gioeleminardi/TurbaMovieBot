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

std::string controller::add_movie(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return std::string("Aggiungimi in un gruppo!");
    }

    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    std::string movie_url;

    auto msg_tokens = StringTools::split(msg->text, ' ');

    if (msg_tokens.size() < 2) {
        return std::string("Utilizzo: /aggiungi <titolo film> [http(s)://<url>]");
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
            return std::string("Turba film già inserito");
        } else {
            return std::string("Errore: ").append(e.what());
        }
    }
    return std::string("Aggiunto!");
}

std::string controller::delete_movie(const TgBot::Message::Ptr& msg) { return ("delete_movie\n"); }

std::string controller::extract_movie(const TgBot::Message::Ptr& msg) { return ("extract_movie\n"); }

std::string controller::my_movies(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return std::string("Aggiungimi in un gruppo!");
    }

    auto user_id = msg->from->id;
    auto group_id = msg->chat->id;

    auto movies = _db_handler.get_user_movies(user_id, group_id);

    auto response = std::string("I tuoi film:\n");

    for (const auto& movie : movies) {
        response.append(movie.title);
        if (!movie.url.empty()) {
            response.append(" (" + movie.url + ")");
        }
        response.append("\n");
    }

    return response;
}

std::unordered_map<std::int32_t, std::vector<model::movie>> controller::all_movies(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return std::unordered_map<std::int32_t, std::vector<model::movie>>();
    }

    auto group_id = msg->chat->id;

    return _db_handler.get_group_movies(group_id);
}

std::string controller::done_watch(const TgBot::Message::Ptr& msg) { return ("done_watch\n"); }

void controller::init() { _db_handler.init_schema(); }
