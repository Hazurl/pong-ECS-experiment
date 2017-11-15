#include <ecs/ecs.hpp>

#include <pong_ecs/ecs_full_config.hpp>

#include <SFML/Graphics.hpp>

#include <ctime>
#include <random>
#include <cmath>
#include <functional>

int main (int, char**) {

    float screen_width = 960;
    float screen_height = 640;

    pong_ecs::ECS_controller controller(
        ecs::SystemsConstructor<pong_ecs::systems::Physics,
                                pong_ecs::systems::InputController,
                                pong_ecs::systems::AIController>(
            [screen_width, screen_height] () { return pong_ecs::systems::Physics(screen_width, screen_height); },
            [screen_height]               () { return pong_ecs::systems::InputController(screen_height); },
            [screen_height]               () { return pong_ecs::systems::AIController(screen_height); }
        )
    );

    srand(time(nullptr));

    const float radius_ball = 12;
    const float speed_ball = 200;
    int ball_horizontal = (((rand() % 2) == 0) ? -1 : 1) * speed_ball;
    int ball_vertical = (((rand() % 2) == 0) ? -1 : 1) * speed_ball;

    float pad_height = 80;
    float pad_width = 20;
    float pad_marge = 20;
    
    float ai_speed = 250;

    auto e_ball = controller.create();
    controller.add_component<pong_ecs::component::Position>     (e_ball, screen_width / 2, screen_height / 2);
    controller.add_component<pong_ecs::component::Velocity>     (e_ball, ball_horizontal, ball_vertical);
    controller.add_component<pong_ecs::component::BoxCollider>  (e_ball, 0, 0, radius_ball * 2, radius_ball * 2);
    controller.add_component<pong_ecs::component::BallSprite>    (e_ball, radius_ball, sf::Color::White);

    auto e_player_pad = controller.create();
    controller.add_component<pong_ecs::component::Position>     (e_player_pad, pad_marge, screen_height / 2);
    controller.add_component<pong_ecs::component::Inputs>       (e_player_pad);
    controller.add_component<pong_ecs::component::BoxCollider>  (e_player_pad, 0, 0, pad_width, pad_height);
    controller.add_component<pong_ecs::component::PadSprite>    (e_player_pad, pad_width, pad_height, sf::Color::White);

    auto const& ball_position = controller.get_component<pong_ecs::component::Position>(e_ball);
    auto e_enemy_pad = controller.create();
    controller.add_component<pong_ecs::component::Position>     (e_enemy_pad, screen_width - pad_marge, screen_height / 2);
    controller.add_component<pong_ecs::component::AI>           (e_enemy_pad, ball_position, ai_speed);
    controller.add_component<pong_ecs::component::BoxCollider>  (e_enemy_pad, 0, 0, pad_width, pad_height);
    controller.add_component<pong_ecs::component::PadSprite>    (e_enemy_pad, pad_width, pad_height, sf::Color::White);

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