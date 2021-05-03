/**
 * \file       turba_commands.hpp
 * \author     Gioele Minardi <gioelem3@gmail.com>
 * \date       5/3/21
 */
#ifndef TURBAMOVIEBOT_COMMANDS_HPP
#define TURBAMOVIEBOT_COMMANDS_HPP

static const std::map<std::string, std::string> BOT_COMMANDS = {
        {"aggiungi",    "Aggiungi un film. Utilizzo: /aggiungi <nome_film> [<url>]"},
        {"rimuovi",     "Rimuovi un film. Utilizzo: /rimuovi <nome_film>"},
        {"estrai",      "Estrai un film da guardare"},
        {"segna_visto", "Rimuovi il film estratto"},
        {"mia_lista",   "Ottieni la lista dei tuoi film"},
        {"lista",       "Ottieni la lista di tutti i film"}
};


#endif //TURBAMOVIEBOT_COMMANDS_HPP
