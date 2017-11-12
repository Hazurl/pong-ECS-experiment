#include <ecs/ecs.hpp>

#include <pong_ecs/ecs_full_config.hpp>

#include <SFML/Graphics.hpp>

#include <ctime>
#include <random>
#include <cmath>
#include <functional>

int main (int, char**) {

    float screen_width = 960;
    float screen_height = 720;

    pong_ecs::ECS_controller controller(
        ecs::SystemsConstructor<pong_ecs::systems::Physics>(
            [screen_width, screen_height] () { return pong_ecs::systems::Physics(screen_width, screen_height); }
        )
    );

    srand(time(nullptr));

    const float radius_ball = 2;
    const float speed_ball = 300;
    const int count_ball = 2000;

    for (int i = 0; i < count_ball; ++i) {
        // create an entity
        // (auto is pong_ecs::Entity)
        auto ent = controller.create();
        controller.add_component<pong_ecs::component::Position>(ent, screen_width / 2, screen_height / 2);
        auto rad = (rand() % 360) * M_PI / 180.;
        const float real_speed = speed_ball * ((rand() % 90) + 10) / 100.;
        controller.add_component<pong_ecs::component::Velocity>(ent, std::cos(rad) * real_speed, std::sin(rad) * real_speed);
        controller.add_component<pong_ecs::component::BoxCollider>(ent, 0, 0, radius_ball * 2, radius_ball * 2);
        controller.add_component<pong_ecs::component::BallSprite>(ent, radius_ball, sf::Color(rand() % 256, rand() % 256, rand() % 256));
    }

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Balls");
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        auto time = clock.restart().asMicroseconds() / 1000000.;

        controller.update(
            static_cast<float>(time), // Time : float
            static_cast<sf::RenderTarget*>(&window) // RenderTarget
        );
        window.display();
    }


    return 0;
}