#pragma once
#include "perlin.h"
#include "rtw_image.h"

namespace Renderer {
	class Texture {
	public:
		virtual Vec3 value(double u, double v, const Vec3& p) const = 0;
	};

	class Solid : public Texture {
	public:
		Solid(const Vec3& alb);

		Solid(double r, double g, double b);

		Vec3 value(double u, double v, const Vec3& p) const;

	private:
		Vec3 albedo;
	};

	class Checkered : public Texture {
	public:
		Checkered(double scale, Texture* e, Texture* o);
		Checkered(double scale, const Vec3& e, const Vec3& o);

		Vec3 value(double u, double v, const Vec3& p) const;

	private:
		double inv;
		Texture* even;
		Texture* odd;
	};

	class ImageTexture : public Texture {
	public:
		ImageTexture(const char* filename);
		Vec3 value(double u, double v, const Vec3& p) const;
	private:
		RTW img;
	};

	class NoiseTexture : public Texture {
	public:
		NoiseTexture();

		Vec3 value(double u, double v, const Vec3& p) const;
	private:
		Perlin noise;
	};
}