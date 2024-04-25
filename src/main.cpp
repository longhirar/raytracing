/*
    https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/anintervalclass
*/

#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "constants.hpp"

const int image_width = 1600;
const int image_height = 900;

double viewport_height = 2.0;
double viewport_width = viewport_height * (double(image_width)/image_height);

color ray_color(const ray& r, const hittable_list& w) {

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5*(unit_direction.y() + 1.0);

    hit_record rec;

    if (w.hit(r, 0, DOUBLE_INF, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    return (1.0-a)*color(1,1,1) + a*color(0.5, 0.7, 1.0);
}

int main() {
    std::clog << "LonghiRT (c++)\n";

    hittable_list world;

    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    point3 camera_center = point3(0,0,0);
    double camera_focal_length = 1.0;

    point3 viewport_upper_left = camera_center - vec3(0, 0, camera_focal_length) - viewport_u/2 - viewport_v/2;
    point3 viewport_rootpixel = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Output

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rRendering Line " << j << " / " << image_height;

        for (int i = 0; i < image_width; i++) {
            
            point3 pixel_center = viewport_rootpixel + (i * pixel_delta_u) + (j * pixel_delta_v);
            ray r = ray(camera_center, pixel_center-camera_center); // from camera center, pointing to pixel on viewport

            color result_color = ray_color(r, world);

            int ir = int(255.999 * result_color.r());
            int ig = int(255.999 * result_color.g());
            int ib = int(255.999 * result_color.b());

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::clog << "\r\nFinished Render!\n";

    return 0;
}
