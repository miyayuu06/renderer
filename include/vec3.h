#pragma once


namespace Renderer {
	class Vec {
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

		Vec();
		Vec(double x, double y, double z);

		double operator[](int i);
		double length();

		Vec operator+(Vec other);
		Vec operator-();
		Vec operator*(double i);
		double dot(Vec other);
		Vec cross(Vec other);
		Vec norm();

		void print();

		void vec_Test();

	private:
	};
}