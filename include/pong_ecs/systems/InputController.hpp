#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class InputController {
public:
    InputController(float screen_height);
    void process(float dt, Views<component::Inputs, component::Position, component::BoxCollider>& entities) const;

    using config = ecs::ctx::make_system<
        InputController,
        ECS_MAKE_METHOD(&InputController::process)
    >;
private:

    float screen_height;

};

}}