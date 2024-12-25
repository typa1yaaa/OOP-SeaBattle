#ifndef GAME_H
#define GAME_H

#pragma once
#include "User.h"
#include "Bot.h"
#include "Observer.h"
#include "GameState.h"

class Game: public Observable{
private:
    std::shared_ptr<User> user;
    std::shared_ptr<Bot> botik;
    std::shared_ptr<GameState> game_state;
    int destroy_user_ship = 0; //количество уничтоженных кораблей юзера (уничтоженных бот кораблей)
    int destroy_bot_ship = 0; //количество уничтоженных кораблей бота (уничтоженных юзер кораблей)
public:
    // определяем юзера и бота
    Game();
    void UpdateGame();
    void StartGame();
    void AttackRound();
    //завершение игры
    void EndGame(int win_flag);
    int RetDestroyUserShip();
    int RetDestroyBotShip();
    void DrawFields();
    User& GetUser();
    void SetUser(User& new_user);
    Bot& GetBot();
    void SetBot(Bot& new_bot);

    void SetDestrShips(int dest_user, int dest_bot);
    // Сохранение игры
    void SaveGame();
    // Загрузка игры
    void LoadGame();

    friend std::ostream& operator<<(std::ostream& out, Game& game);
    friend std::istream& operator>>(std::istream& in, Game& game);
};



#endif //GAME_H