#pragma once

namespace pong_ecs {
namespace component {

struct Velocity {
    Velocity(float x, float y) : x(x), y(y) {}
    float x, y;
};

}}