#ifndef RENDERER_H_
#define RENDERER_H_

#include "base_module.hpp"
#include "menu_builder.hpp"
#include "game_builder.hpp"
#include <SFML/Graphics.hpp>
#include "event.hpp"

class renderer : public base_module {
 public:
    renderer();
    int on_event(const event & e) override;
 private:
    sf::RenderWindow window;
    menu_builder menu_bldr;
    game_builder game_bldr;
};

#endif  // RENDERER_H_
