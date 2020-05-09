#ifndef NEAREST_POINTS_POINT_H
#define NEAREST_POINTS_POINT_H

#include <vector>

struct Point {
	double x;
	double y;
};

/// nearestPoints should return a new vector (list) with the `n` points out of the parameter `points` which are closest
/// (euclidean distance) to `center`.
/// \param center Reference point for the distance.
/// \param points The list of points to find the nearest ones.
/// \param n Number of points to return.
/// \return vector with the nearest points.
std::vector<Point> nearestPoints(const Point &center, const std::vector<Point> &points, const size_t n);

#endif
