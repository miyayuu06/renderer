#pragma once
#include "aabb.h"
#include <cmath>
#include <limits>

namespace Renderer {
	class Material;

	class HitProperties {
	public:
		Vec3 intersectionPoint;
		Vec3 normal;
		Material* mat;
		double tValue;
		double u;
		double v;
		bool frontFace;

		void correctFrontalOrientation(const Ray &r) {
			frontFace = (r.dir().dot(normal) < 0.0);
			normal = frontFace ? normal : -normal;
		}
	};

	class Hittable {
	public:
		virtual bool hit(const Interval& i, const Ray& r, HitProperties& prop) const = 0;
		virtual AABB boundingBox() const = 0;
	};

	class Translation : public Hittable {
	public:
		Translation(Hittable* obj, const Vec3& offset) : obj(obj), offset(offset) {
			bbox = obj->boundingBox() + offset;
		}

		bool hit(const Interval& i, const Ray& r, HitProperties& prop) const {
			Ray offsetRay(r.origin() - offset, r.dir(), r.tm());

			if (!obj->hit(i, offsetRay, prop)) {
				return false;
			}
			
			prop.intersectionPoint += offset;
			return true;

		}

		AABB boundingBox() const {
			return bbox;
		}

	private:
		Hittable* obj;
		Vec3 offset;
		AABB bbox;
	};

	class RotationY : public Hittable {
	public:
		RotationY(Hittable* obj, double angle) : obj(obj) {
			double radians = angle * 3.1415926535 / 180.0;
			cosTheta = cos(radians);
			sinTheta = sin(radians);
			bbox = obj->boundingBox();

			Vec3 min(std::numeric_limits<double>::infinity());
			Vec3 max = -min;

			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					for (int k = 0; k < 2; k++) {
						double x = i * bbox.x.maximum + (1 - i) * bbox.x.minimum;
						double y = j * bbox.y.maximum + (1 - j) * bbox.y.minimum;
						double z = k * bbox.z.maximum + (1 - k) * bbox.z.minimum;

						double newX = cosTheta * x + sinTheta * z;
						double newZ = -sinTheta * x + cosTheta * z;

						Vec3 aux(newX, y, newZ);

						min.x = fmin(min.x, aux[0]);
						min.y = fmin(min.y, aux[1]);
						min.z = fmin(min.z, aux[2]);

						max.x = fmax(max.x, aux[0]);
						max.y = fmax(max.y, aux[1]);
						max.z = fmax(max.z, aux[2]);
					}
				}
			}

			bbox = AABB(min, max);
		}

		bool hit(const Interval& i, const Ray& r, HitProperties& prop) const {
			Vec3 origin(r.origin().x * cosTheta + r.origin().z * sinTheta,
				r.origin().y, -r.origin().x * sinTheta + r.origin().z * cosTheta);

			Vec3 direction(r.dir().x * cosTheta + r.dir().z * sinTheta,
				r.dir().y, -r.dir().x * sinTheta + r.dir().z * cosTheta);

			Ray rotatedRay(origin, direction, r.tm());

			if (!obj->hit(i, rotatedRay, prop)) {
				return false;
			}

			prop.intersectionPoint = Vec3(cosTheta * prop.intersectionPoint.x - sinTheta * prop.intersectionPoint.z, 
				prop.intersectionPoint.y, sinTheta * prop.intersectionPoint.x + cosTheta * prop.intersectionPoint.z);

			prop.normal = Vec3(cosTheta * prop.normal.x - sinTheta * prop.normal.z,
				prop.normal.y, sinTheta * prop.normal.x + cosTheta * prop.normal.z);

			prop.correctFrontalOrientation(rotatedRay);

			return true;

		}

		AABB boundingBox() const {
			return bbox;
		}

	private:
		Hittable* obj;
		AABB bbox;
		double cosTheta;
		double sinTheta;
	};
}