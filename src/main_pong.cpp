#include <ecs/ecs.hpp>

#include <pong_ecs/ecs_full_config.hpp>

#include <ctime>
#include <random>
#include <cmath>
#include <functional>

int main (int, char**) {

    float screen_width = 1000;
    float screen_height = 1000;

    pong_ecs::ECS_controller controller(
        ecs::SystemsConstructor<mtp::List<pong_ecs::systems::Physics>>(
            [screen_width, screen_height] () { return pong_ecs::systems::Physics(screen_width, screen_height); }
        )
    );

    srand(time(nullptr));

    const float radius_ball = 10;

    //for (int i = 0; i < 100; ++i) {
        // create an entity
        // (auto is pong_ecs::Entity)
        auto ent = controller.controller.create();
        controller.controller.add_component<pong_ecs::component::Position>(ent, screen_width / 2, screen_height / 2);
        auto rad = (rand() % 360) * M_PI / 180.;
        rad = 0;
        controller.controller.add_component<pong_ecs::component::Velocity>(ent, std::cos(rad), std::sin(rad));
        controller.controller.add_component<pong_ecs::component::BoxCollider>(ent, -radius_ball/2., -radius_ball/2, radius_ball, radius_ball);
    //}

    // while(true) {

        // finally update all systems, 
        // be careful deltaTime is a float, so you HAVE to pass a float
        controller.update(0.42f); 
        controller.update(0.42f); 
        controller.update(0.42f); 
        controller.update(0.42f); 
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