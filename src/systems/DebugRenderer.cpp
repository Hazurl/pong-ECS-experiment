#include <pong_ecs/systems/DebugRenderer.hpp>

namespace pong_ecs {
namespace systems {

void DebugRenderer::render_boxcollider(Views<component::BoxCollider, component::Position> const& entities, sf::RenderTarget* renderTarget) const {
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

void DebugRenderer::render_transform(Views<component::Position> const& entities, sf::RenderTarget* renderTarget) const {
    for(auto const& view : entities) {
        auto const& position = view.get<component::Position>();
        sf::Vertex up[2];
        sf::Vertex right[2];

        up[0].position = right[0].position = {position.x, position.y};
        up[1].position = {position.x, position.y + 10};
        right[1].position = {position.x + 10, position.y};

        up[0].color = up[1].color = sf::Color::Red;
        right[0].color = right[1].color = sf::Color::Blue;
        renderTarget->draw(up, 2, sf::PrimitiveType::Lines);
        renderTarget->draw(right, 2, sf::PrimitiveType::Lines);
    }
}

}}