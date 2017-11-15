#include <pong_ecs/systems/AIController.hpp>

namespace pong_ecs {
namespace systems {

AIController::AIController(float screen_height) : screen_height(screen_height) {}

void AIController::process(float dt, Views<component::AI, component::Position, component::BoxCollider>& entities) const {
    for (auto& view : entities) {
        auto const& ai = view.get<component::AI>();
        auto const& ball_pos = ai.ball;
        auto max_dist = ai.speed * dt;

        auto& pos = view.get<component::Position>();
        auto const& box = view.get<component::BoxCollider>();

        float y_center = pos.y + box.offset_y + box.height / 2.;

        float dist = (ball_pos.y - y_center) * dt;
        if (dist > max_dist)
            dist = max_dist;
        else if (dist < -max_dist)
            dist = -max_dist;

        pos.y += dist;
        if (pos.y + box.offset_y < 0) {
            pos.y = 0 - box.offset_y;
        } else if(pos.y + box.offset_y + box.height > screen_height) {
            pos.y = screen_height - (box.offset_y + box.height);
        }
    }
}

}}