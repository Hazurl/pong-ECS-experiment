#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class Physics {
public:

    using config = ecs::ctx::make_system<
        Physics,
        ecs:::ctx::make_system_methods<
            ECS_SYST_METHOD( Physics::update )
            // or
            //ecs::ctx::make_system_method< decltype(&Physics::update), Physics::update>
        >
    >;

    Physics(float screen_width, float screen_height);

    void update(float dt, Views<component::Position, component::Velocity, component::BoxColiider>& entities) const;

private:

    void update_one(float dt, component::Position& position, component::Velocity& velocity, component::BoxCollider& boxCollider) const; 

    float screen_width, screen_height;

};

}}