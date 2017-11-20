#include <pong_ecs/systems/Renderer.hpp>

namespace pong_ecs {
namespace systems {

void Renderer::render_balls(TagController& tag_controller, Views<component::BallSprite, component::Position> const& entities, sf::RenderTarget* renderTarget) const {
    for(auto const& view : entities) {
        auto const& position = view.get<component::Position>();
        auto const& ballSprite = view.get<component::BallSprite>();
        Entity ent = view.entity();
        sf::CircleShape ball;
        ball.setRadius(ballSprite.radius);
        ball.setFillColor(ballSprite.color);
        if (tag_controller.template has<tags::ball>(ent.id()) && tag_controller.template has<tags::fancy>(ent.id()))
            ball.setFillColor(sf::Color::Magenta);
        ball.setPosition(position.x, position.y);

        //std::cout << "Draw at " << position.x << ", " << position.y << "; radius " << ballSprite.radius << std::endl;

        renderTarget->draw(ball);
    }
}

void Renderer::render_pads(Views<component::PadSprite, component::Position> const& entities, sf::RenderTarget* renderTarget) const {
    for(auto const& view : entities) {
        auto const& position = view.get<component::Position>();
        auto const& padSprite = view.get<component::PadSprite>();
        sf::RectangleShape pad;
        pad.setSize({padSprite.width, padSprite.height});
        pad.setFillColor(padSprite.color);
        pad.setPosition(position.x, position.y);

        //std::cout << "Draw at " << position.x << ", " << position.y << "; radius " << ballSprite.radius << std::endl;

        renderTarget->draw(pad);
    }
}

}}