#pragma once

#include <pong_ecs/ecs_sub_config.hpp>
#include <array>

namespace pong_ecs {
namespace systems {

class FPS {
public:
    FPS();
    void show(float dt, sf::RenderTarget* renderTarget);

    using config = ecs::ctx::make_system<
        FPS,
        //ecs::ctx::make_method< decltype(&Physics::update), &Physics::update >
        // or
        ECS_MAKE_METHOD(&FPS::show)
    >;

private:

    static constexpr int size = 100;
    std::array<float, size> old_fps;
    int pointer = 0;

    sf::Font font;

};

}}