#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include "abilities/AbilitiesManager.h"
#include "game/Game.h"
#include "lb4/Observer.h"

#include <algorithm>
#include "lb4/InputProcessor.h"
#include "lb4/GameDisplay.h"
#include "lb4/GameMenagement.h"
#include "part_field/Cell.h"

int main() {
    Game game;

    InputProcessor input_processor;
    GameMenagement<InputProcessor> game_management(game, input_processor);
    FieldRendering field_render;
    GameDisplay<FieldRendering> game_display(game, field_render);
    
    game.StartGame();
    while (true) {
        try {
            game_management.CallCommand();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}