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
    component::BoxCollider>;

// Limit size
using Limit_size = ecs::ctx::make_limit_size<2048>;

// Grow Policy
using Grow_policy = ecs::ctx::make_grow_policy<ecs::instant_grow_policy>;

// Entities Controller, use in argument (in systems) to control creation/destruction of entities
// + addition/deletion of components
using EntitiesController = ecs::ctx::make_entity_controller<Entity, Components, Limit_size, Grow_policy>;

// Views, use to iterate over all entities with components
template<typename...Cs>
using Views = ecs::ctx::make_views<Entity, Cs...>;

}