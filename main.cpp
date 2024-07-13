#include "utility.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <chrono>

// int main() {
//     hittable_list world;
//
//     auto material_ground = make_shared<lambertian>(color(0.5, 0.5, 0.5));
//     auto material_center = make_shared<lambertian>(color(0.0, 0.34, 0.71));
//     auto material_left   = make_shared<dielectric>(1.50);
//     auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
//     auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.2);
//
//     world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
//     world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
//     world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
//     world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
//     world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
//
//     camera cam;
//
//     cam.aspect_ratio = 16.0 / 9.0;
//     cam.image_width  = 400;
//     cam.samples_per_pixel = 300;
//     cam.max_depth = 50;
//
//     cam.vfov = 25;
//     cam.lookfrom = point3(-2,2,1);
//     cam.lookat   = point3(0,0,-1);
//     cam.vup      = vec3(0,1,0);
//
//     cam.defocus_angle = 10.0;
//     cam.focus_dist    = 3.4;
//
//     cam.render(world);
//
//     return 0;
// }

int main() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.55));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.1, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.0, 0.34, 0.71));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(1.0, 0.12, 0.20), 0.0);
    // auto material3 = make_shared<metal>(color(1.0, 0.64, 0.0), 0.2);
    world.add(make_shared<sphere>(point3(4, 1.0, 0), 1.0, material3));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 500;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    auto start = std::chrono::high_resolution_clock::now();
    cam.render(world);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    // Print the duration
    std::cout << "Render time: " << duration.count() << " seconds" << std::endl;
}