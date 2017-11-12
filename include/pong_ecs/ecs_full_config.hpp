#pragma once

#include <pong_ecs/ecs_sub_config.hpp>
#include <pong_ecs/systems/Systems.hpp>

namespace pong_ecs {

// Systems List
// Remember, they are updated in order
using Systems = ecs::ctx::make_systems<
    systems::Physics::config,
    systems::Renderer::config,/*
    systems::ColliderRenderer::config*/
    systems::FPS::config
>;

// Final ECS

using ECS_controller = ecs::ctx::make_ecs<
    Entity,
    Components,
    Systems,

    Limit_size,
    Grow_policy
>;

}