#include <pong_ecs/systems/ColliderRenderer.hpp>

namespace pong_ecs {
namespace systems {

void ColliderRenderer::render_box(Views<component::BoxCollider, component::Position> const& entities, sf::RenderTarget* renderTarget) const {
    for(auto const& view : entities) {
        auto const& position = view.get<component::Position>();
        auto const& boxCollider = view.get<component::BoxCollider>();
        sf::RectangleShape box;
        box.setPosition(boxCollider.offset_x + position.x, boxCollider.offset_y + position.y);
        box.setSize({boxCollider.width, boxCollider.height});
        box.setOutlineColor(sf::Color::Green);
        box.setFillColor(sf::Color::Transparent);
        box.setOutlineThickness(1);

        renderTarget->draw(box);
    }
}

}}