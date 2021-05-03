/**
 * \file       bot.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#include "bot.hpp"

bot::bot(const std::string &token) : _bot{token}, _long_poll{_bot} {
}

void bot::init() {
    TgBot::BotCommand::Ptr cmd;
    std::vector<TgBot::BotCommand::Ptr> commands;
    for (const auto &command : BOT_COMMANDS) {
        cmd = std::make_shared<TgBot::BotCommand>();
        cmd->command = command.first;
        cmd->description = command.second;
        commands.push_back(cmd);
    }
    _bot.getApi().setMyCommands(commands);

    _bot.getEvents().onAnyMessage([this](const TgBot::Message::Ptr &msg) {
        parse_cmd(msg);
    });
}

void bot::run() {

    try {
        std::cout << "Bot: " << _bot.getApi().getMe()->username << std::endl;
        while (true) {
            _long_poll.start();
        }
    } catch (TgBot::TgException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

void bot::parse_cmd(const TgBot::Message::Ptr &msg) {
    printf("parse_cmd: %s from %s\n", msg->text.c_str(), msg->from->username.c_str());
    auto cmd_dirty = msg->text;
    std::string cmd;
    if (!StringTools::startsWith(cmd_dirty, "/")) {
        printf("%s is not a command\n", cmd_dirty.c_str());
        return;
    }

    if (cmd_dirty.find('@') != std::string::npos) {
        auto str_tokens = StringTools::split(cmd_dirty, '@');
        cmd = str_tokens[0];
    }

    printf("CMD: %s\n", cmd.c_str());
    if ("/aggiungi" == cmd) {
        //add_movie()
    }
}

void bot::add_movie(std::string title, std::string resource_url) {
    printf("add_movie\n");
}

void bot::delete_movie(std::string title) {
    printf("delete_movie\n");
}

std::string bot::extract_movie() {
    printf("extract_movie\n");
    return std::string();
}

void bot::my_movies() {
    printf("my_movies\n");
}

void bot::all_movies() {
    printf("all_movies\n");
}

bot::~bot() = default;