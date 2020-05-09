#include <queue>
#include <math.h>

#include "Point.h"

using namespace std;

/// Calculates the euclidean distance between two points
/// \param a First point.
/// \param b Second point.
/// \return The euclidean distance.
inline double distance(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

vector<Point> nearestPoints(const Point &center, const vector<Point> &points, const size_t n) {
	if (n == 0) {
		return vector<Point>();
	}
	if (n > points.size()) {
		return vector<Point>(points);
	}

	auto compare = [&center](const Point &a, const Point &b) {
		return distance(a, center) < distance(b, center);
	};

	priority_queue<Point, vector<Point>, decltype(compare)> nearest(compare);
	for (auto &point : points) {
		if (nearest.size() >= n && compare(point, nearest.top())) {
			nearest.pop();
			nearest.emplace(point);
		} else if (nearest.size() < n) {
			nearest.emplace(point);
		}
	}

	vector<Point> resp(n);
	size_t index = 0;
	while (!nearest.empty()) {
		resp[index++] = nearest.top();
		nearest.pop();
	}

	return std::move(resp);
}
