#pragma once
namespace Renderer {
	class Vec3 {
	public:
		union {
			double _coordinates[3];
			struct {
				double x;
				double y;
				double z;
			};
			struct {
				double r;
				double g;
				double b;
			};
		};

		Vec3();
		Vec3(double v);
		Vec3(double x, double y, double z);

		double operator[](int i) const;
		double length() const;
		double lengthSquared() const;

		Vec3 operator+(const Vec3& other) const;
		Vec3& operator+=(const Vec3& other);
		Vec3 operator-(const Vec3& other) const;

		Vec3 operator-() const;
		Vec3 operator*(double i) const;
		static Vec3 Vec3Mult(const Vec3& u, const Vec3& v);
		Vec3& operator*=(double i);
		Vec3 operator/(double i) const;
		double dot(const Vec3& other) const;
		Vec3 cross(const Vec3& other) const;
		Vec3 norm() const;

		static Vec3 random(double min, double max);
		static Vec3 random();
		static Vec3 randomUnitVector();
		static Vec3 randomUnitVectorInDisk();
		static Vec3 RUVHemisphereCorrector(const Vec3& surfaceNormal);

		bool nearZero();
		static Vec3 reflect(const Vec3& v, const Vec3& n);
		static Vec3 refraction(const Vec3& r, const Vec3& n, double etaProportion);

	private:
	};
}