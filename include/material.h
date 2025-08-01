#pragma once

#include "hittable.h"

namespace Renderer {
	class Material {
	public:
		virtual ~Material() = default;
		virtual bool scatter(const Ray& r, const HitProperties& prop, Vec3& colorAtenuation, Ray& scatteredRay) = 0;
	};

	class Lambertian : public Material {
	public:
		Lambertian(const Vec3& alb) : albedo(alb) {}
		inline bool scatter(const Ray& r, const HitProperties& prop, Vec3& colorAtenuation, Ray& scatteredRay) {
			Vec3 scatterDirection = prop.normal + Vec3::randomUnitVector();

			if (scatterDirection.nearZero()) {
				scatterDirection = prop.normal;
			}

			scatteredRay = Ray(prop.intersectionPoint, scatterDirection);
			colorAtenuation = albedo;

			return true;
		}
	private:
		Vec3 albedo;
	};

	class Metal : public Material {
	public:
		Metal(const Vec3& alb) : albedo(alb) {}
		inline bool scatter(const Ray& r, const HitProperties& prop, Vec3& colorAtenuation, Ray& scatteredRay) {
			Vec3 reflectedRay = Vec3::reflect(r.dir(), prop.normal);
			scatteredRay = Ray(prop.intersectionPoint, reflectedRay);
			colorAtenuation = albedo;
			return true;
		}
	private:
		Vec3 albedo;
	};
}