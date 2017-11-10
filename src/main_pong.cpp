#include <ecs/ecs.hpp>

#include <pong_ecs/ecs_full_config.hpp>

#include <ctime>
#include <random>
#include <cmath>

int main (int, char**) {

    pong_ecs::ECS_controller controller;

    srand(time(nullptr));

    float screen_width = 640;
    float screen_height = 480;
    const float radius_ball = 10;

    for (int i = 0; i < 100; ++i) {
        // create an entity
        // (auto is pong_ecs::Entity)
        auto ent = controller.create();
        controller.add<pong_ecs::component::Position>(ent, screen_width / 2, screen_height / 2);
        auto rad = (rand() % 360) * M_PI / 180.;
        controller.add<pong_ecs::component::Velocity>(ent, std::cos(rad), std::sin(rad));
        controller.add<pong_ecs::component::CollisionBox>(ent, -radius_ball/2., -radius_ball/2, radius_ball, radius_ball);
    }

    // while(true) {

        // finally update all systems, 
        // be careful deltaTime is a float, so you HAVE to pass a float
        controller.update(0.42f); 
        // 0.42 is a double, so it would complain about it

        // I recommend making an alias for each type :
        /*
            using Time = float;
            controller.update(Time{0.42});

            // System's signature
            void update(Time dt);
        */

    //}

    return 0;
}