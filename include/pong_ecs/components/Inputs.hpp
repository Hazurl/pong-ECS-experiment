#pragma once

#include <SFML/Graphics.hpp>

namespace pong_ecs {
namespace component {

struct Inputs {
    static sf::Keyboard::Key up;
    static sf::Keyboard::Key down;
};

}}