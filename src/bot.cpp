/**
 * \file       bot.cpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#include "bot.hpp"

#include "controller.hpp"
#include "emojis.hpp"
#include "utils.hpp"

bot::bot(const std::string& token)
    : _bot{token}
    , _long_poll{_bot}
    , _controller{std::make_unique<controller>()} {}

void bot::init() {
    _commands.emplace_back("aggiungi", "Aggiungi un film. Utilizzo: /aggiungi <nome_film> [<url>]", [&](const TgBot::Message::Ptr& msg) {
        auto status = _controller->add_movie(msg);
        std::string response;
        switch (status) {
        case status::ok:
            response = "Film aggiunto";
            break;
        case status::error:
            response = "Errore sconosciuto";
            break;
        case status::not_found:
            response = "Film non trovato";
            break;
        case status::not_a_group:
            response = "Aggiungimi in un gruppo";
            break;
        case status::malformed_cmd:
            response = "Utilizzo: /aggiungi <nome_film> [<url>]";
            break;
        case status::already_saved:
            response = "Film esistente";
            break;
        }
        _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
    });

    _commands.emplace_back("rimuovi", "Rimuovi un film. Utilizzo: /rimuovi <id_film>", [&](const TgBot::Message::Ptr& msg) {
        auto status = _controller->delete_movie(msg);
        std::string response;
        switch (status) {
        case status::ok:
            response = "Film eliminato";
            break;
        case status::error:
            response = "Errore sconosciuto";
            break;
        case status::not_found:
            response = "Film non trovato";
            break;
        case status::not_a_group:
            response = "Aggiungimi in un gruppo";
            break;
        case status::malformed_cmd:
            response = "Utilizzo: /rimuovi <id_film>";
            break;
        default:
            response = "Errore critico";
            break;
        }

        response.append("\n");
        _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
    });

    _commands.emplace_back("estrai", "Estrai un film da guardare", [&](const TgBot::Message::Ptr& msg) {
        auto result = _controller->extract_movie(msg);

        std::string response = emoji_map[emoji::movie_camera] + " Turba Estrazione " + emoji_map[emoji::movie_camera] + "\n\n";

        std::string user_movie_response_template = "~~~~~~~~~~\nTurbato: %s\nFilm: %s\nUrl: %s\n";

        if (result.empty()) {
            response = "Non ci sono film in lista";
            _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
            return;
        }

        for (const auto& movie : result) {
            std::string url = "N/A";
            auto user_id = movie.user_id;
            auto chat_member = _bot.getApi().getChatMember(msg->chat->id, user_id);
            auto username = chat_member->user->username;
            if (!movie.url.empty()) {
                url = movie.url;
            }

            response.append(string_format(user_movie_response_template, username.c_str(), movie.title.c_str(), url.c_str()));
        }

        auto local_msg = _bot.getApi().sendMessage(msg->chat->id, response, true);
        _bot.getApi().pinChatMessage(msg->chat->id, local_msg->messageId);
    });

    _commands.emplace_back("segna_visto", "Rimuovi il film estratto", [&](const TgBot::Message::Ptr& msg) {
        auto status = _controller->done_watch(msg);
        std::string response;
        if (status == status::ok) {
            response = "Segnato";
        }
        if (!response.empty()) {
            _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
        }
    });

    _commands.emplace_back("mia_lista", "Ottieni la lista dei tuoi film", [&](const TgBot::Message::Ptr& msg) {
        auto my_movies = _controller->my_movies(msg);
        std::string response = emoji_map[emoji::movie_camera] + " I tuoi film " + emoji_map[emoji::movie_camera] + "\n\n";
        std::string movie_emoji;

        if (my_movies.empty()) {
            response.append("La tua lista è vuota");
            _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
            return;
        }

        for (const auto& movie : my_movies) {
            switch (movie.status) {
            case model::movie_status::watched:
                movie_emoji = emoji_map[emoji::heavy_check_mark];
                break;
            case model::movie_status::extracted:
                movie_emoji = emoji_map[emoji::eye];
                break;
            default:
                movie_emoji = "";
                break;
            }
            response.append(movie_emoji).append(" ").append(movie.title);
            if (!movie.url.empty()) {
                response.append(" (" + movie.url + ")");
            }
            response.append(" [" + std::to_string(movie.id) + "]");
            response.append("\n");
        }

        _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
    });

    _commands.emplace_back("lista", "Ottieni la lista di tutti i film", [&](const TgBot::Message::Ptr& msg) {
        auto res = _controller->all_movies(msg);

        std::string response = emoji_map[emoji::movie_camera] + " Turba Lista " + emoji_map[emoji::movie_camera] + "\n\n";
        std::string movie_emoji;

        if (res.empty()) {
            response.append("Vuota!");
            _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
            return;
        }

        for (const auto& map_entry : res) {
            auto user_id = map_entry.first;
            auto user_movies = map_entry.second;
            auto chat_member = _bot.getApi().getChatMember(msg->chat->id, user_id);
            auto username = chat_member->user->username;
            response.append("<strong>" + username + "</strong>: \n");
            for (const auto& movie : user_movies) {
                switch (movie.status) {
                case model::movie_status::watched:
                    movie_emoji = emoji_map[emoji::heavy_check_mark];
                    break;
                case model::movie_status::extracted:
                    movie_emoji = emoji_map[emoji::eye];
                    break;
                default:
                    movie_emoji = "";
                    break;
                }
                response.append(movie_emoji).append(" ").append(movie.title);
                if (!movie.url.empty()) {
                    response.append(" (" + movie.url + ")");
                }
                response.append(" [" + std::to_string(movie.id) + "]");
                response.append("\n");
            }
            response.append("\n");
        }

        _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId, nullptr, "HTML");
    });

    _commands.emplace_back("swap", "Inverti due film. Utilizzo: /swap <film_id1> <film_id2>", [&](const TgBot::Message::Ptr& msg) {
        auto res = _controller->swap_movies(msg);
        std::string response;
        switch (res) {
        case status::ok:
            response = "Film scambiati";
            break;
        case status::error:
            response = "Errore sconosciuto";
            break;
        case status::not_found:
            response = "Film non trovato";
            break;
        case status::not_a_group:
            response = "Aggiungimi in un gruppo";
            break;
        case status::malformed_cmd:
            response = "Utilizzo: /swap <film_id1> <film_id2>";
            break;
        default:
            response = "Errore critico";
            break;
        }

        response.append("\n");
        _bot.getApi().sendMessage(msg->chat->id, response, true, msg->messageId);
    });

    load_commands();
}

void bot::run() {
    _controller->init();
    bool getMe = false;
    while (true) {
        try {
            if (!getMe) {
                std::cout << "Bot: " << _bot.getApi().getMe()->username << std::endl;
                getMe = true;
            }
            _long_poll.start();
        } catch (TgBot::TgException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
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