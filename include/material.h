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

			scatteredRay = Ray(prop.intersectionPoint, scatterDirection, r.tm());
			colorAtenuation = albedo;

			return true;
		}
	private:
		Vec3 albedo;
	};

	class Metal : public Material {
	public:
		Metal(const Vec3& alb, double fuzz) : albedo(alb) {
			fuzziness = fuzz < 1 ? fuzz : 1;
		}
		inline bool scatter(const Ray& r, const HitProperties& prop, Vec3& colorAtenuation, Ray& scatteredRay) {
			Vec3 reflectedRay = Vec3::reflect(r.dir(), prop.normal);
			reflectedRay = (reflectedRay + Vec3::randomUnitVector() * fuzziness).norm();
			scatteredRay = Ray(prop.intersectionPoint, reflectedRay, r.tm());
			colorAtenuation = albedo;
			return true;
		}
	private:
		Vec3 albedo;
		double fuzziness;
	};

	class Dielectric : public Material {
	public:
		Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

		inline bool scatter(const Ray& r, const HitProperties& prop, Vec3& colorAtenuation, Ray& scatteredRay) {
			colorAtenuation = Vec3(1.0);
			Vec3 normalisedRayDir = r.dir().norm();
			double eta = prop.frontFace ? (1.0 / refractionIndex) : refractionIndex;

			double cosTheta = fmin(-normalisedRayDir.dot(prop.normal), 1.0);
			double sinTheta = sqrt(abs(1.0 - cosTheta * cosTheta));

			Vec3 scatteredRayDirection;

			if (eta * sinTheta > 1.0 || reflectance(cosTheta, eta) > random()) {
				scatteredRayDirection = Vec3::reflect(normalisedRayDir, prop.normal);
			}
			else {
				scatteredRayDirection = Vec3::refraction(normalisedRayDir, prop.normal, eta);
			}
			scatteredRay = Ray(prop.intersectionPoint, scatteredRayDirection, r.tm());
			return true;
		}

	private:
		double refractionIndex;

		static double reflectance(double cosT, double ri) {
			double r0 = (1 - ri) / (1 + ri);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow(1 - cosT, 5);
		}
	};
}