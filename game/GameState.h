#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "User.h"
#include "Bot.h"
#include <fstream>
#include <sstream>

class GameState {

public:
    void LoadGame(std::shared_ptr<User> user, std::shared_ptr<Bot> bot, int* destroy_user_ship, int* destroy_bot_ship);
    void SaveGame(std::shared_ptr<User> user, std::shared_ptr<Bot> bot, int* destroy_user_ship, int* destroy_bot_ship);
};
#endif //GAMESTATE_H