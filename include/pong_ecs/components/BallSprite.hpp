#pragma once

#include <SFML/Graphics.hpp>

namespace pong_ecs {
namespace component {

struct BallSprite {
    BallSprite(float radius, sf::Color const& color) : radius(radius), color(color) {}

    float radius;
    sf::Color color;
};

}}