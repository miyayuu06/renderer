#include "interval.h"

namespace Renderer {
	Interval::Interval() {}

	Interval::Interval(double mini, double maxi) : minimum(mini), maximum(maxi) {
	}

	Interval::Interval(const Interval& a, const Interval& b) {
		minimum = a.minimum <= b.minimum ? a.minimum : b.minimum;
		maximum = a.maximum >= b.maximum ? a.maximum : b.maximum;
	}

	bool Interval::belongs(double t) const {
		return (t > minimum) && (t < maximum);
	}

	double Interval::mini() const {
		return minimum;
	}

	double Interval::maxi() const {
		return maximum;
	}

	Interval Interval::expand(double delta) {
		return Interval(minimum - delta / 2, maximum + delta / 2);
	}
}