#pragma once

namespace Renderer {
	class Interval {
	public:
		Interval();
		Interval(double mini, double maxi);
		Interval(const Interval& a, const Interval& b);
		bool belongs(double t) const;
		double mini() const;
		double maxi() const;
		Interval expand(double delta);

		double clamp(double x) const;

		double minimum;
		double maximum;
	};
}