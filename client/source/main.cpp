#include <SFML/Graphics.hpp>

int main() {
    int start_red_car_x = 414.f;
    int start_red_car_y = 571.f;
    int start_blue_car_x = 414.f;
    int start_blue_car_y = 601.f;
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Bauman Racing");

    sf::Texture map_texture;
    if (!map_texture.loadFromFile("res/map.png"))
        return EXIT_FAILURE;
    sf::Sprite map_sprite(map_texture);
    
    sf::Texture red_car_texture;
    if (!red_car_texture.loadFromFile("res/red_car.png"))
        return EXIT_FAILURE;
    sf::Sprite red_car_sprite(red_car_texture);
    red_car_sprite.setPosition(start_red_car_x, start_red_car_y);
    
    sf::Texture blue_car_texture;
    if (!blue_car_texture.loadFromFile("res/blue_car.png"))
        return EXIT_FAILURE;
    sf::Sprite blue_car_sprite(blue_car_texture);
    blue_car_sprite.setPosition(start_blue_car_x, start_blue_car_y);
    
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                start_red_car_x--;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                start_red_car_x++;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                start_red_car_y--;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                start_red_car_y++;
            }
        }
        
        red_car_sprite.setPosition(start_red_car_x, start_red_car_y);
        window.clear();
        window.draw(map_sprite);
        window.draw(red_car_sprite);
        window.draw(blue_car_sprite);
        window.display();
    }
    return 0;
    
}
