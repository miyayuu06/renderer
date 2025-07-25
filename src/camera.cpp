#include "camera.h"

namespace Renderer {
    Vec3 Camera::ray_color(HittableList& scenery, Ray& r) {

        // Possible collision with hittables

        HitProperties record;
        Interval rangeOfRender(0.0001, INFINITY);
        if (scenery.hit(rangeOfRender, r, record)) {
            return (record.normal + Vec3(1.0, 1.0, 1.0)) * 0.5;
        }

        // Background

        Vec3 unitVec3tor = r.dir().norm();
        double a = (unitVec3tor.y + 1.0) * 0.5;
        return (Vec3(1.0, 1.0, 1.0) * (1.0 - a)) + (Vec3(0.5, 0.7, 1.0) * a);
    }

    void Camera::initialize() {

    }
}