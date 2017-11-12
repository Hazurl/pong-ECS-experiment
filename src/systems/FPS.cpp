#include <pong_ecs/systems/FPS.hpp>
#include <numeric>

namespace pong_ecs {
namespace systems {

FPS::FPS() {
    std::fill(old_fps.begin(), old_fps.end(), 0);
    font.loadFromFile("fonts/Roboto-Regular.ttf");
}

void FPS::show(float dt, sf::RenderTarget* renderTarget) {
    old_fps[pointer] = (1. / dt);
    pointer = (pointer + 1) % size;

    float fps = std::accumulate(old_fps.begin(), old_fps.end(), 0.) / size;

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(static_cast<int>(fps)));
    text.setColor(sf::Color::White);
    text.setCharacterSize(30);

    renderTarget->draw(text);
}

}}