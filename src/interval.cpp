#include "interval.h"

namespace Renderer {
	Interval::Interval(double mini, double maxi) {
		minimum = mini;
		maximum = maxi;
	}

	bool Interval::belongs(double t) {
		return (t > minimum) && (t < maximum);
	}
}