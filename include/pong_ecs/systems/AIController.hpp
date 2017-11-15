#pragma once

#include <pong_ecs/ecs_sub_config.hpp>

namespace pong_ecs {
namespace systems {

class AIController {
public:
    AIController(float screen_height);
    void process(float dt, Views<component::AI, component::Position, component::BoxCollider>& entities) const;

    using config = ecs::ctx::make_system<
        AIController,
        ECS_MAKE_METHOD(&AIController::process)
    >;
private:

    float screen_height;

};

}}