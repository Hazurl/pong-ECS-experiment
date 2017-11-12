#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class Renderer {
public:
    void render(Views<component::BallSprite, component::Position> const& entities, sf::RenderTarget* renderTarget) const;

    using config = ecs::ctx::make_system<
        Renderer,
        ECS_MAKE_METHOD(&Renderer::render)
    >;
};

}}