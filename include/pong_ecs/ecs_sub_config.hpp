#pragma once

#include <pong_ecs/components/Components.hpp>

#include <ecs/ecs.hpp>

namespace pong_ecs {

// Entity use in our ecs
using Entity = ecs::ctx::default_entity;

// Components list
using Components = ecs::ctx::make_components<
    component::Position, 
    component::Velocity, 
    component::CollisionBox>;

// Entities Controller, use in argument (in systems) to control creation/destruction of entities
// + addition/deletion of components
using EntitiesController = ecs::ctx::make_entities_controller<Entity, Components>;

// Views, use to iterate over all entities with components
template<typename...Cs>
using Views = ecs::ctx::make_views<Entity, Cs...>;

// Limit size
static constexpr int Limit_size = ecs::ctx::default_limit_size;

// Grow Policy
using Grow_policy = ecs::ctx::default_grow_policy;

}