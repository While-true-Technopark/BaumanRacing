#include "renderer.hpp"

renderer::renderer():
    window(sf::VideoMode(1280, 720), "Bauman Racing") {

}

int renderer::on_event(const event & e) {
    return 1;
}
