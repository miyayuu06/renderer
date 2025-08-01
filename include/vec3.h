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

		Vec3 operator+(const Vec3& other) const;
		Vec3& operator+=(const Vec3& other);
		Vec3 operator-(const Vec3& other) const;

		Vec3 operator-() const;
		Vec3 operator*(double i) const;
		Vec3& operator*=(double i);
		Vec3 operator/(double i) const;
		double dot(const Vec3& other) const;
		Vec3 cross(const Vec3& other) const;
		Vec3 norm() const;

		/*void print();
		void Vec3_Test();*/

	private:
	};
}