#include <pong_ecs/systems/Physics.hpp>

namespace pong_ecs {
namespace systems {

Physics::Physics (float screen_width, float screen_height)
    : screen_width(screen_width), screen_height(screen_height) {}


void Physics::update(float dt, Views<component::Position, component::Velocity, component::BoxCollider>& entities) const {
    for(auto& view : entities) {
        auto& position = view.get<component::Position>();
        auto& velocity = view.get<component::Velocity>();
        auto& boxCollider = view.get<component::BoxCollider>();

        update_one(dt, position, velocity, boxCollider);
    }
}

void Physics::update_one(float dt,
                         component::Position& position, 
                         component::Velocity& velocity, 
                         component::BoxCollider& boxCollider) const {
    
    component::Position next_pos(position.x + velocity.x * dt, 
                                 position.y + velocity.y * dt);

    float next_left = next_pos.x + boxCollider.offset_x;
    float next_right = next_pos.x + boxCollider.offset_x + boxCollider.width;
    float next_top = next_pos.y + boxCollider.offset_y;
    float next_bottom = next_pos.y + boxCollider.offset_y + boxCollider.height;

    float left = position.x + boxCollider.offset_x;
    float right = position.x + boxCollider.offset_x + boxCollider.width;
    float top = position.y + boxCollider.offset_y;
    float bottom = position.y + boxCollider.offset_y + boxCollider.height;
    
    // collision
    if (next_left < 0) {
        // left border
        float impact_time = -left / velocity.x;
        float remainder_time = dt - impact_time;
        velocity.x = -velocity.x;
        next_pos.x = velocity.x * remainder_time;
    }
    else if (next_right > screen_width) {
        // rigth border
        float impact_time = (screen_width - right) / velocity.x;
        float remainder_time = dt - impact_time;
        velocity.x = -velocity.x;
        next_pos.x = screen_width - (boxCollider.offset_x + boxCollider.width) + velocity.x * remainder_time;
    }
    if (next_top < 0) {
        // top border
        float impact_time = -top / velocity.y;
        float remainder_time = dt - impact_time;
        velocity.y = -velocity.y;
        next_pos.y = velocity.y * remainder_time;
    }
    else if (next_bottom > screen_height) {
        // bottom border
        float impact_time = (screen_height - bottom) / velocity.y;
        float remainder_time = dt - impact_time;
        velocity.y = -velocity.y;
        next_pos.y = screen_height - (boxCollider.offset_y + boxCollider.height) + velocity.y * remainder_time;
    }

    position = next_pos;
}

}}