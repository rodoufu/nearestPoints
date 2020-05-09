#include <vector>
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

/// nearestPoints should return a new vector (list) with the `n` points out of the parameter `points` which are closest
/// (euclidean distance) to `center`.
///
/// Complexity: O(n + m * log(n))
/// Considering `m = points.size()`, with `n <= m`.
/// \param center Reference point for the distance.
/// \param points The list of points to find the nearest ones.
/// \param n Number of points to return.
/// \return vector with the nearest points.
vector<Point> nearestPoints(const Point &center, const vector<Point> &points, const size_t n) {
	if (n == 0) {
		// O(1)
		return vector<Point>();
	}
	if (n > points.size()) {
		// O(m) < O(n)
		return vector<Point>(points);
	}

	auto compare = [&center](const Point &a, const Point &b) {
		return distance(a, center) < distance(b, center);
	};

	priority_queue<Point, vector<Point>, decltype(compare)> nearest(compare);
	// O(m * (1 + 1 + log (n)) = O(m * log(n))
	for (auto &point : points) {
		if (nearest.size() >= n && compare(point, nearest.top())) {
			// O(1)
			nearest.pop();
			// O(1)
			nearest.emplace(point);
		} else if (nearest.size() < n) {
			// O(log(n))
			nearest.emplace(point);
		}
	}

	vector<Point> resp(n);
	size_t index = 0;
	// O(n)
	while (!nearest.empty()) {
		resp[index++] = nearest.top();
		nearest.pop();
	}

	return std::move(resp);
}
