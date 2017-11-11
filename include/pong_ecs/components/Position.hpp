#pragma once

namespace pong_ecs {
namespace component {

struct Position {
    Position(float x, float y) : x(x), y(y) {}
    float x, y;
};

}}