#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class Physics {
public:
    Physics(float screen_width, float screen_height);

    void update(float dt, Views<component::Position, component::Velocity, component::BoxCollider>& entities) const;

    using config = ecs::ctx::make_system<
        Physics,
        //ecs::ctx::make_method< decltype(&Physics::update), &Physics::update >
        // or
        ECS_MAKE_METHOD(&Physics::update)
    >;

private:

    void update_one(float dt, component::Position& position, component::Velocity& velocity, component::BoxCollider& boxCollider) const; 

    float screen_width, screen_height;

};

}}