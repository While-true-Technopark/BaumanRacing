#ifndef LOADER_H_
#define LOADER_H_

#include <thread>
#include <unordered_map>
#include <utility>

#include "event.hpp"
#include "loader_abst.hpp"

class loader : public loader_abst {
 public:
    loader();
    int load_all() override;
    sf::Texture* get_texture(const std::string & name) override;
    bool is_loaded() override;
 private:
    std::string textures_dir;
    std::unordered_map<std::string, sf::Texture> textures;
    std::thread load_thread;

    int load_textures();
};

#endif  // LOADER_H_
