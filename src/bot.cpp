/**
 * \file       bot.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#include "bot.hpp"

#include "controller.hpp"

bot::bot(const std::string& token)
    : _bot{token}
    , _long_poll{_bot}
    , _controller{std::make_unique<controller>()} {}

void bot::init() {
    _commands.emplace_back("aggiungi", "Aggiungi un film. Utilizzo: /aggiungi <nome_film> [<url>]", [&](auto msg) {
        auto ret = _controller->add_movie(msg);
        _bot.getApi().sendMessage(msg->chat->id, ret);
    });
    _commands.emplace_back("rimuovi", "Rimuovi un film. Utilizzo: /rimuovi <nome_film>", [&](auto msg) { _controller->delete_movie(msg); });
    _commands.emplace_back("estrai", "Estrai un film da guardare", [&](auto msg) { _controller->extract_movie(msg); });
    _commands.emplace_back("segna_visto", "Rimuovi il film estratto", [&](auto msg) { _controller->done_watch(msg); });
    _commands.emplace_back("mia_lista", "Ottieni la lista dei tuoi film", [&](auto msg) { _controller->my_movies(msg); });
    _commands.emplace_back("lista", "Ottieni la lista di tutti i film", [&](auto msg) { _controller->all_movies(msg); });

    load_commands();
}

void bot::run() {
    _controller->init();
    try {
        std::cout << "Bot: " << _bot.getApi().getMe()->username << std::endl;
        while (true) {
            _long_poll.start();
        }
    } catch (TgBot::TgException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void bot::load_commands() {
    TgBot::BotCommand::Ptr cmd;
    std::vector<TgBot::BotCommand::Ptr> commands;
    for (const auto& command : _commands) {
        cmd = std::make_shared<TgBot::BotCommand>();
        cmd->command = command.cmd;
        cmd->description = command.description;
        commands.push_back(cmd);
    }

    _bot.getApi().setMyCommands(commands);

    for (const auto& _cmd : _commands) {
        _bot.getEvents().onCommand(_cmd.cmd, _cmd.callback);
    }
}

bot::~bot() = default;