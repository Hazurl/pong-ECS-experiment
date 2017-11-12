#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class ColliderRenderer {
public:
    void render_box(Views<component::BoxCollider, component::Position> const& entities, sf::RenderTarget* renderTarget) const;

    using config = ecs::ctx::make_system<
        ColliderRenderer,
        ECS_MAKE_METHOD(&ColliderRenderer::render_box)
    >;
};

}}