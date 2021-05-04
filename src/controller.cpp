/**
 * \file       controller.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#include "controller.hpp"

#include <tgbot/tools/StringTools.h>

#include <iostream>

#include "model/turba_entry.hpp"

controller::controller() = default;

controller::~controller() = default;

std::string controller::add_movie(const TgBot::Message::Ptr& msg) {
    if (msg->chat->type != TgBot::Chat::Type::Group) {
        return std::string("Not a group chat");
    }

    auto username = msg->from->username;
    auto groupname = msg->chat->title;

    std::string movieurl = "N/A";

    auto msg_tokens = StringTools::split(msg->text, ' ');

    if (msg_tokens.size() < 2) {
        return std::string("Not enough parameters");
    }

    auto movietitle = msg_tokens[1];

    if (msg_tokens.size() == 3) {
        movieurl = msg_tokens[2];
    }

    printf("add_movie [Username: %s, Groupname: %s, Movietitle: %s, Movieurl: %s]", username.c_str(), groupname.c_str(), movietitle.c_str(),
           movieurl.c_str());

    std::stringstream ss;
    ss << "add_movie [Username: " << username << ", Groupname: " << groupname << ", Movietitle: " << movietitle
       << ", Movieurl: " << movieurl << "]" << std::endl;

    return ss.str();
}

std::string controller::delete_movie(const TgBot::Message::Ptr& msg) { return ("delete_movie\n"); }

std::string controller::extract_movie(const TgBot::Message::Ptr& msg) { return ("extract_movie\n"); }

std::string controller::my_movies(const TgBot::Message::Ptr& msg) { return ("my_movies\n"); }

std::string controller::all_movies(const TgBot::Message::Ptr& msg) { return ("all_movies\n"); }

std::string controller::done_watch(const TgBot::Message::Ptr& msg) { return ("done_watch\n"); }

void controller::init() { _db_handler.init_schema(); }
