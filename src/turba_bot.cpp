/**
 * \file       turba_bot.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#include "turba_bot.hpp"

turba_bot::turba_bot(const std::string &token) : _bot{token}, _long_poll{_bot} {
}

void turba_bot::init() {
    TgBot::BotCommand::Ptr cmd;
    std::vector<TgBot::BotCommand::Ptr> commands;
    for (const auto &command : turba_ns::commands) {
        cmd = std::make_shared<TgBot::BotCommand>();
        cmd->command = command.first;
        cmd->description = command.second;
        commands.push_back(cmd);
    }
    _bot.getApi().setMyCommands(commands);

    _bot.getEvents().onAnyMessage([this](const TgBot::Message::Ptr &msg) {
        command_handler(msg);
    });
}

void turba_bot::run() {

    try {
        std::cout << "Bot: " << _bot.getApi().getMe()->username << std::endl;
        while (true) {
            _long_poll.start();
        }
    } catch (TgBot::TgException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

void turba_bot::command_handler(const TgBot::Message::Ptr &msg) {
    std::cout << "Received: " << msg->text << " from " << msg->from->username << std::endl;
}

turba_bot::~turba_bot() = default;