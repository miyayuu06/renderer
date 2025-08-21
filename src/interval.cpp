#include "interval.h"

namespace Renderer {
	Interval::Interval(double mini, double maxi) : minimum(mini), maximum(maxi) {
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