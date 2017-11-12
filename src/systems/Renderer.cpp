#include <pong_ecs/systems/Renderer.hpp>

namespace pong_ecs {
namespace systems {

void Renderer::render(Views<component::BallSprite, component::Position> const& entities, sf::RenderTarget* renderTarget) const {
    for(auto const& view : entities) {
        auto const& position = view.get<component::Position>();
        auto const& ballSprite = view.get<component::BallSprite>();
        sf::CircleShape ball;
        ball.setRadius(ballSprite.radius);
        ball.setFillColor(ballSprite.color);
        ball.setPosition(position.x, position.y);

        //std::cout << "Draw at " << position.x << ", " << position.y << "; radius " << ballSprite.radius << std::endl;

        renderTarget->draw(ball);
    }
}

}}