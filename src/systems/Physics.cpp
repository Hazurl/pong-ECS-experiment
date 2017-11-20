#include <pong_ecs/systems/Physics.hpp>

namespace pong_ecs {
namespace systems {

Physics::Physics (float screen_width, float screen_height)
    : screen_width(screen_width), screen_height(screen_height) {}


void Physics::update(float dt, Views<component::Position, component::Velocity, component::BoxCollider>& entities, TagController& tag_controller) const {
    for (auto view_it = entities.begin(); view_it != entities.end(); ++view_it) {
        auto& view = *view_it;
        auto& position = view.get<component::Position>();
        auto& velocity = view.get<component::Velocity>();
        auto& boxCollider = view.get<component::BoxCollider>();

        update_position(dt, position, velocity);
        screen_collision(tag_controller, view.entity(), position, velocity, boxCollider);
        for (auto view_it2 = view_it + 1; view_it2 != entities.end(); ++view_it2)
            dual_collision(position, velocity, boxCollider, view_it2->get<component::Position>(), 
                                                            view_it2->get<component::Velocity>(),
                                                            view_it2->get<component::BoxCollider>());

    }
}

void Physics::update_position(float dt, component::Position& position, component::Velocity& velocity) const {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Physics::screen_collision(TagController& tag_controller, Entity ent,
                               component::Position& position, 
                               component::Velocity& velocity, 
                               component::BoxCollider& boxCollider) const {
    float left   = position.x + boxCollider.offset_x;
    float right  = position.x + boxCollider.offset_x + boxCollider.width;
    float top    = position.y + boxCollider.offset_y;
    float bottom = position.y + boxCollider.offset_y + boxCollider.height;
    
    if (left < 0 || right > screen_width) {
        velocity.x = -velocity.x;
        if (tag_controller.template has<tags::ball>(ent.id())) {
            tag_controller += [ent] (auto& controller) {
                controller.template set<tags::fancy>(ent.id());
            };
        }  
    }
    if (top < 0 || bottom > screen_height) {
        velocity.y = -velocity.y;
        if (tag_controller.template has<tags::ball>(ent.id())) {
            tag_controller += [ent] (auto& controller) {
                controller.template remove<tags::fancy>(ent.id());
            };
        }
    }
}

void Physics::dual_collision(component::Position& pos1, component::Velocity& vel1, component::BoxCollider& box1,
                             component::Position& pos2, component::Velocity& vel2, component::BoxCollider& box2) const {

    float left1   = pos1.x + box1.offset_x;
    float right1  = pos1.x + box1.offset_x + box1.width;
    float top1    = pos1.y + box1.offset_y;
    float bottom1 = pos1.y + box1.offset_y + box1.height;

    float left2   = pos2.x + box2.offset_x;
    float right2  = pos2.x + box2.offset_x + box2.width;
    float top2    = pos2.y + box2.offset_y;
    float bottom2 = pos2.y + box2.offset_y + box2.height;

}

}}