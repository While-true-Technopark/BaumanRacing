#ifndef LOADER_ABST_H_
#define LOADER_ABST_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>

#include "event.hpp"


class loader_abst {
 public:
    virtual int load_all() = 0;
    virtual sf::Texture* get_texture(const std::string & name) = 0;
    virtual sf::Font* get_font(const std::string & name) = 0;
    virtual sf::Music* get_sound(const std::string & name) = 0;
    virtual bool is_loaded() = 0;
    virtual ~loader_abst() = default;
 protected:
    bool loaded;
};

#endif  // LOADER_ABST_H_
