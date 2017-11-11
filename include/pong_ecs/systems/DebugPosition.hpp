#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class DebugPosition {
public:
    DebugPosition() = default;

    void debug(Views<component::Position> const& entities) const {
        for (auto const& view : entities) {
            auto const& position = view.get<component::Position>();
            std::cout << "Entity " << view.entity() << " at (" << position.x << ", " << position.y << ")" << std::endl;
        }
    }

    using config = ecs::ctx::make_system<
        DebugPosition,
        ecs::ctx::make_method< decltype(&DebugPosition::debug), &DebugPosition::debug >
    >;
};


}}