#pragma once

namespace Renderer {
	class Interval {
	public:
		Interval(double mini, double maxi);
		bool belongs(double t);

	private:
		double minimum;
		double maximum;
	};
}