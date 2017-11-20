#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class DebugRenderer {
public:
    void render_boxcollider(Views<component::BoxCollider, component::Position> const& entities, sf::RenderTarget* renderTarget) const;
    void render_transform(Views<component::Position> const& entities, sf::RenderTarget* renderTarget) const;

    using config = ecs::ctx::make_system<
        DebugRenderer,
        ECS_MAKE_METHOD(&DebugRenderer::render_boxcollider),
        ECS_MAKE_METHOD(&DebugRenderer::render_transform)
    >;
};

}}