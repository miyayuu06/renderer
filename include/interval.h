#pragma once

namespace Renderer {
	class Interval {
	public:
		Interval(double mini, double maxi);
		bool belongs(double t) const;
		double mini() const;
		double maxi() const;

	private:
		double minimum;
		double maximum;
	};
}