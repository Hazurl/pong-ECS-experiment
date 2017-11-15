#pragma once

#include <pong_ecs/ecs_entity_config.hpp>
#include <pong_ecs/components/Position.hpp>

namespace pong_ecs {
namespace component {

struct AI {
    AI(Position const& ball, float speed) : ball(ball), speed(speed) {}
    Position const& ball;
    float speed;
};

}}