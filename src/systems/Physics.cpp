#include <pong_ecs/systems/Physics.hpp>

namespace pong_ecs {
namespace systems {

Physics::Physics (float screen_width, float screen_height)
    : screen_width(screen_width), screen_height(screen_height) {}


void Physics::update(float dt, Views<component::Position, component::Velocity, component::BoxCollider>& entities) {
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
    
    component::Position next_pos = { position.x + velocity.x * dt, position.y + velocity.y * dt };
    
    // collision
    if ((next_pos.x + boxCollider.offset_x) < 0) {
        // left border
        float impact_time = -(position.x + boxCollider.offset_x) / velocity.x;
        float remainder_time = dt - impact_time;
        velocity.x *= -1;
        next_pos.x = velocity.x * remainder_time;
    }
    else if ((next_pos.x + boxCollider.offset_x + boxCollider.width) > screen_width) {
        // rigth border
        float impact_time = (screen_width - position.x + boxCollider.offset_x + boxCollider.width) / velocity.x;
        float remainder_time = dt - impact_time;
        velocity.x *= -1;
        next_pos.x = screen_width + velocity.x * remainder_time;
    }
    if ((next_pos.y + boxCollider.offset_y) < 0) {
        // top border
        float impact_time = -(position.y + boxCollider.offset_y) / velocity.y;
        float remainder_time = dt - impact_time;
        velocity.y *= -1;
        next_pos.y = velocity.y * remainder_time;
    }
    else if ((next_pos.y + boxCollider.offset_y + boxCollider.heigth) > screen_heigth) {
        // bottom border
        float impact_time = (screen_heigth - position.y + boxCollider.offset_y + boxCollider.heigth) / velocity.y;
        float remainder_time = dt - impact_time;
        velocity.y *= -1;
        next_pos.y = screen_heigth + velocity.y * remainder_time;
    }

    position = newt_pos;
}

}}