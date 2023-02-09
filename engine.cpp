#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#define _USE_MATH_DEFINES

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 20;
const double FOV = M_PI / 4; // field of view in radians

struct Vector2 {
    double x, y;
};

struct Vector3 {
    double x, y, z;

    Vector3 operator+(const Vector3 &other) const {
        return { x + other.x, y + other.y, z + other.z };
    }
};

struct Wall {
    Vector2 a, b;
};

struct Player {
    Vector2 pos;
    double angle;
};

int main() {
    std::vector<Wall> walls = {
        {{0, 0}, {0, 10}},
        {{0, 10}, {10, 10}},
        {{10, 10}, {10, 0}},
        {{10, 0}, {0, 0}},
    };
    Player player = {{5, 5}, 0};

    while (true) {
        std::vector<double> z_buffer(SCREEN_WIDTH, std::numeric_limits<double>::max());
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            double ray_angle = (player.angle - FOV / 2) + (FOV * x / SCREEN_WIDTH);

            // cast a ray from the player's position and find the closest wall
            double distance = std::numeric_limits<double>::max();
            Vector2 wall_hit;
            Vector2 hit_normal;
            for (const Wall &wall : walls) {
                Vector2 intersection;
                if (intersect_ray_with_segment(player.pos, ray_angle, wall.a, wall.b, intersection)) {
                    double d = distance_between(player.pos, intersection);
                    if (d < distance) {
                        distance = d;
                        wall_hit = intersection;
                        hit_normal = normal_of_wall(wall);
                    }
                }
            }

            // calculate the height of the wall slice on the screen
            int wall_slice_height = SCREEN_HEIGHT / distance * 2;
            int wall_start = -wall_slice_height / 2 + SCREEN_HEIGHT / 2;
            int wall_end = wall_slice_height / 2 + SCREEN_HEIGHT / 2;
            if (wall_start < 0) wall_start = 0;
            if (wall_end >= SCREEN_HEIGHT) wall_end = SCREEN_HEIGHT - 1;

            // shade the wall slice based on the angle of the normal
            double light_intensity = dot_product(hit_normal, normalize(Vector3{0, 1, 0}));
            char slice_char = (light_intensity > 0.5) ? '#' : '.';

            // store the Z-value (distance) of the wall slice in the Z-buffer
            z_buffer[x] = distance;

            // draw the wall slice
            for (int y = wall_start; y <= wall_end; y++) {
std::cout << slice_char;
}
}
    std::cout << std::endl;

    // update player position and angle based on user input
    // ...
}

return 0;
