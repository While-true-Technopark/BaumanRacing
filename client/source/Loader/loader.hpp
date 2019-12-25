#ifndef LOADER_H_
#define LOADER_H_

#include <thread>
#include <unordered_map>
#include <utility>

#include "event.hpp"
#include "loader_abst.hpp"

#define LDR_OK 0
#define LDR_FILE_NOT_LOADED -1

class loader : public loader_abst {
 public:
    loader();
    int load_all() override;
    sf::Texture* get_texture(const std::string & name) override;
    sf::Font* get_font(const std::string & name) override;
    sf::Music* get_sound(const std::string & name) override;

    ~loader() override;
    bool is_loaded() override;
 private:
    bool sound_loaded;

    std::thread* load_thread;
    std::string static_dir;

    std::vector<std::string> textures_paths;
    std::unordered_map<std::string, sf::Texture> textures;

    std::vector<sf::Font> fonts;
    std::vector<std::string> fonts_paths;

    std::vector<sf::Music> sounds;
    std::vector<std::string> sounds_paths;

    int load_all_static();
};

#endif  // LOADER_H_
