#pragma once

namespace pong_ecs {
namespace component {

struct BoxCollider {
    BoxCollider(float offset_x, float offset_y, float width, float height) : offset_x(offset_x), offset_y(offset_y), width(width), height(height) {}
    float offset_x, offset_y;
    float width, height;
};

}}