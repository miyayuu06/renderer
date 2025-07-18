#pragma once


namespace Renderer {
	class Vec {
	public:
		double _coordinates[3];
		Vec();
		Vec(double x, double y, double z);

		double operator[](int i);
		double length();

		Vec operator+(Vec other);
		Vec operator-();
		Vec operator*(double i);
		double dot(Vec other);
		Vec cross(Vec other);

		void print();

		void vec_Test();

	private:
	};
}