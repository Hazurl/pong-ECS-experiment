#include <pong_ecs/systems/InputController.hpp>

namespace pong_ecs {
namespace systems {

InputController::InputController(float screen_height) : screen_height(screen_height) {}

void InputController::process(float dt, Views<component::Inputs, component::Position, component::BoxCollider>& entities) const {
    float move = (sf::Keyboard::isKeyPressed(component::Inputs::down) 
                - sf::Keyboard::isKeyPressed(component::Inputs::up));

    if (move != 0) {
        move *= dt * 150;
        for (auto& view : entities) {
            auto& pos = view.get<component::Position>();
            pos.y += move;
            auto const& box = view.get<component::BoxCollider>();
            if (pos.y + box.offset_y < 0) {
                pos.y = 0 - box.offset_y;
            } else if(pos.y + box.offset_y + box.height > screen_height) {
                pos.y = screen_height - (box.offset_y + box.height);
            }
        }
    }
}

}}