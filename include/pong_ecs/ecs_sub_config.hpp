#pragma once

#include <pong_ecs/components/Components.hpp>
#include <pong_ecs/ecs_entity_config.hpp>

#include <ecs/ecs.hpp>

namespace pong_ecs {

// Components list
using Components = ecs::ctx::make_components<
    component::Position, 
    component::Velocity, 
    component::BoxCollider,
    component::BallSprite,
    component::PadSprite,
    component::Inputs,
    component::AI>;

// Limit size
using Limit_size = ecs::ctx::make_limit_size<16384>;

// Grow Policy
using Grow_policy = ecs::ctx::make_grow_policy<ecs::instant_grow_policy>;

namespace tags {
    struct ball {};
    struct pad {};
    struct player {};
    struct enemy {};

    struct fancy {};
}

// Tags
using Tags = ecs::ctx::make_tags<tags::ball, tags::pad, tags::player, tags::enemy, tags::fancy>;
using TagController = ecs::ctx::make_tag_controller<Tags, Limit_size>;

// Entities Controller, use in argument (in systems) to control creation/destruction of entities
// + addition/deletion of components
using EntitiesController = ecs::ctx::make_entity_controller<Entity, Components, Limit_size, Grow_policy>;

// Views, use to iterate over all entities with components
template<typename...Cs>
using Views = ecs::ctx::make_views<Entity, Cs...>;

}