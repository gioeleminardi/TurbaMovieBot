/**
 * \file       controller.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/4/21
 */
#include "controller.hpp"

void controller::add_movie(const TgBot::Message::Ptr& msg) { printf("add_movie\n"); }

void controller::delete_movie(const TgBot::Message::Ptr& msg) { printf("delete_movie\n"); }

std::string controller::extract_movie(const TgBot::Message::Ptr& msg) {
    printf("extract_movie\n");
    return std::string();
}

void controller::my_movies(const TgBot::Message::Ptr& msg) { printf("my_movies\n"); }

void controller::all_movies(const TgBot::Message::Ptr& msg) { printf("all_movies\n"); }

void controller::done_watch(const TgBot::Message::Ptr& msg) { printf("done_watch\n"); }
