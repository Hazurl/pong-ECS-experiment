#pragma once

#include <SFML/Graphics.hpp>

namespace pong_ecs {
namespace component {

struct PadSprite {
    PadSprite(float width, float height, sf::Color const& color) : width(width), height(height), color(color) {}

    float width, height;
    sf::Color color;
};

}}