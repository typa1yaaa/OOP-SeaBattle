#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include "Game.h"                // для класса Game
#include "Observer.h"            // для наследования от Observer
#include "FieldRendering.h"      // предполагается, что класс FieldRendering где-то определен


// шаблонныый класс отображения игры
template <typename FieldRendering>
// класс отслеживания изменения 
class GameDisplay: public Observer{
private:
    Game& game; //
    FieldRendering field_render;
public:
    // конструктор - принимает объект игры и инициализирует рендер
    explicit GameDisplay(Game& new_game, FieldRendering& new_fieldrender)
        : game(new_game), field_render(new_fieldrender) {
            game.add_observer(this);//подписываемся на игру
        }

    void update() override{
        field_render.draw_fields(game.GetUser(), game.GetBot());
    }
};



#endif // GAMEDISPLAY_H
