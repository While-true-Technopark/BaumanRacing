#ifndef CONFIG_H_
#define CONFIG_H_

#include <SFML/Network.hpp>

const size_t DIM = 2;
const size_t DOF = DIM + 1;  // x, y, angle

const size_t PORT = 5555;
const std::string IP = "127.0.0.1";

const sf::Time UPDATE_TIME_OUT = sf::seconds(0.05f);
const sf::Time PING_TIME_OUT = sf::seconds(30.0f);
const sf::Time CONNECT_TIME_OUT = 3.0f * PING_TIME_OUT;

const sf::Time TIME_OUT_BEFORE_START = sf::seconds(3.0f);
const sf::Time TLL_SIDE_OBJECT = sf::seconds(10.0f);

const size_t CARS_TEXTURES_NUMBER = 3;

#endif  // CONFIG_H_
