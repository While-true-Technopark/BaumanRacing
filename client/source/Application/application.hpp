#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SFML/Graphics.hpp>

#include "base_manager.hpp"

#include "game_context.hpp"
#include "game_context_manager.hpp"
#include "input.hpp"
#include "input_manager.hpp"
#include "loader.hpp"
#include "loader_manager.hpp"
#include "network.hpp"
#include "network_manager.hpp"
#include "renderer.hpp"
#include "renderer_manager.hpp"

class application {
 public:
    bool run();
    static application& get_instance();
 private:
    application();

    sf::RenderWindow window;
    game_context_manager game_context_mngr;
    input_manager input_mngr;
    loader_manager loader_mngr;
    network_manager network_mngr;
    renderer_manager renderer_mngr;
};

#endif  // APPLICATION_H_
