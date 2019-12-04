#ifndef LOADER_ABST_H_
#define LOADER_ABST_H_

#include <SFML/Graphics.hpp>
#include <vector>

#include "event.hpp"


class loader_abst {
 public:
    virtual int load_all() = 0;
    virtual sf::Texture* get_texture(const std::string & name) = 0;
    virtual bool is_loaded() = 0;
 protected:
    bool loaded;
    std::vector<std::string> paths;
};

#endif  // LOADER_ABST_H_
